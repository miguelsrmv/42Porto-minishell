/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/17 22:23:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_builtin(t_command_table *current,
			char **envp, t_memptr memptr)
{
	int	original_stdin;
	int	original_stdout;

	current->command_no = 1;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	check_redirections(NULL, &current, memptr);
	if (current->input_fd)
		close(current->input_fd);
	if (current->output_fd)
		close(current->output_fd);
	execute_builtin(current, envp, memptr);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (0);
}

int	execute_builtin(t_command_table *current,
			char **envp, t_memptr memptr)
{
	int		(*function_pointer)(char **, char **, t_command_table *current);
	int		exit_value;

	function_pointer
		= (int (*)(char **, char **,
				t_command_table *))current->builtin_pointer;
	exit_value = function_pointer(current->cmd, envp, current);
	(void)memptr;
	return (exit_value);
}

void	process_parent(int process_num, t_memptr *memptr, int pid)
{
	int	status;
	int	value;

	(void)pid;
	status = 0;
	value = 0;
	set_signal_during_processes_parent();
	while (process_num--)
		waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		value = WEXITSTATUS(status);
	clean_memory(*memptr);
	memptr->return_value = value;
	g_status_flag = value;
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
	clean_memory(memptr);
	exit(g_status_flag);
}
