/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/11 18:45:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_command_table *current,
			char **envp, t_memptr memptr)
{
	int		(*function_pointer)(char **, char **);
	int		exit_value;

	set_signal_during_processes_child();
	function_pointer
		= (int (*)(char **, char **))current->builtin_pointer;
	exit_value = function_pointer(current->cmd, envp);
	clean_memory(memptr);
	return (exit_value);
}

void	process_parent(int process_num,
			t_memptr *memptr)
{
	int	status;
	int	value;

	status = 0;
	set_signal_during_processes_parent();
	while (process_num--)
		wait(&status);
	clean_memory(*memptr);
	if (WIFEXITED(status))
		value = WEXITSTATUS(status);
	memptr->return_value = value;
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
	set_signal_during_processes_child();
	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else if (current->command_type == BUILTIN)
		execute_builtin(current, envp, memptr);
}
