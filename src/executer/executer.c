/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/23 17:09:43 by mde-sa--         ###   ########.fr       */
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
		close(original_stdout);
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
	return (g_status_flag);
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

// Introduzed a pseudo-wait function
void	process_parent(int process_num, t_memptr *memptr, int pid)
{
	(void)pid;
	(void)process_num;
	(void)memptr;

	set_signal_during_processes_parent();
	waitpid(-1, &g_status_flag, 0);
	if (WIFEXITED(g_status_flag))
		g_status_flag = WEXITSTATUS(g_status_flag);
	else if (WIFSIGNALED(g_status_flag))
		g_status_flag = WTERMSIG(g_status_flag + 128);
	//ft_fprintf(2, "FINISHED A PROCESS WITH STATUS %i\n", g_status_flag);
}

void	process_child(int **pipe_fd, t_command_table *current,
			char **envp, t_memptr memptr)
{
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

void	process_forks(t_command_table **command_table, char **envp,
			int process_num, t_memptr memptr)
{
	int				**pipe_fd;
	int				i;
	int				pid;
	t_command_table	*current;

	pipe_fd = NULL;
	pipe_fd = create_pipes(pipe_fd, process_num - 1, &memptr);
	current = *command_table;
	i = 0;
	while (i++ < process_num)
	{
		pid = fork();
		if (pid < 0)
			exit_error(FORK_ERROR, memptr);
		else if (pid == 0)
		{
			current->command_no = i;
			process_child(pipe_fd, current, envp, memptr);
		}
		current = current->next;
	}
	i = 0;
	while (pipe_fd[i])
	{
		if (close(pipe_fd[i][0]) == -1)
			exit_error(CLOSE_ERROR, memptr);
		if (close(pipe_fd[i++][1]) == -1)
			exit_error(CLOSE_ERROR, memptr);
	}
	i = 0;
	while (i++ < process_num)
		process_parent(process_num, &memptr, pid);
	clean_memory(memptr);
	memptr.return_value = g_status_flag;
}
