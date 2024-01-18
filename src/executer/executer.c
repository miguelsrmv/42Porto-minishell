/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/18 21:56:34 by mde-sa--         ###   ########.fr       */
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
	if (check_redirections(NULL, &current, memptr) != VALID)
	{
		close(original_stdin);
		close(original_stdin);
		return (1);
	}
	if (current->input_fd)
		close(current->input_fd);
	if (current->output_fd)
		close(current->output_fd);
	g_status_flag = execute_builtin(current, envp, memptr);
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
	(void)pid;
	set_signal_during_processes_parent();
	while (process_num--)
		waitpid(-1, &g_status_flag, 0);
	if (WIFEXITED(g_status_flag))
		g_status_flag = WEXITSTATUS(g_status_flag);
	clean_memory(*memptr);
	memptr->return_value = g_status_flag;
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
	if (check_redirections(pipe_fd, &current, memptr) != VALID)
		exit(g_status_flag);
	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else if (current->command_type == BUILTIN)
		execute_builtin(current, envp, memptr);
	clean_memory(memptr);
	exit(g_status_flag);
}
