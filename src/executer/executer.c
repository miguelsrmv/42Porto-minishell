/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/17 10:56:27 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_command_table *current,
			char **envp, t_memptr memptr)
{
	int		(*function_pointer)(char **, char **, t_command_table *current);
	int		exit_value;

	function_pointer
		= (int (*)(char **, char **,
				t_command_table *))current->builtin_pointer;
	exit_value = function_pointer(current->cmd, envp, current);
	clean_memory(memptr);
	return (exit_value);
}

void	process_parent(int process_num, t_memptr *memptr, int pid)
{
	int	status;
	int	value;

	(void)pid;
	status = 0;
	set_signal_during_processes_parent();
	while (process_num--)
		waitpid(-1, &status, 0);
	clean_memory(*memptr);
	if (WIFEXITED(status))
		value = WEXITSTATUS(status);
	memptr->return_value = value;
	// Para retirar depois, é uma espécie de sleep
	for (int i = 0; i < 10000; i++)
		;
}

void	process_forks(t_command_table **command_table, char **envp,
			int process_num, t_memptr memptr)
{
	int				**pipe_fd;
	t_command_table	*current;

	pipe_fd = NULL;
	pipe_fd = create_pipes(pipe_fd, process_num - 1, &memptr);
	current = create_processes(command_table, process_num);
	close_pipes(pipe_fd, current, memptr);
	check_redirections(pipe_fd, &current, memptr);
	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else if (current->command_type == BUILTIN)
		execute_builtin(current, envp, memptr);
	close(pipe_fd[current->command_no - 2][0]);
	close(pipe_fd[current->command_no - 1][1]);
}
