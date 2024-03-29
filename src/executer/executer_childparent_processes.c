/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_childparent_processes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:43:18 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 15:56:39 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_parent(int **pipe_fd, int process_num, int *pid_array,
	t_memptr *memptr)
{
	int	i;

	i = 0;
	set_signal_during_processes_parent();
	close_parent_pipes(pipe_fd, process_num, *memptr);
	while (i < process_num)
		waitpid(pid_array[i++], &g_status_flag, 0);
	if (WIFEXITED(g_status_flag))
		g_status_flag = WEXITSTATUS(g_status_flag);
	else if (WIFSIGNALED(g_status_flag))
		g_status_flag = WTERMSIG(g_status_flag) + 128;
	memptr->return_value = g_status_flag;
	free(pid_array);
	if (g_status_flag == SIGINT_SIGNAL)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (g_status_flag == SIGQUIT_SIGNAL)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

void	process_child(int **pipe_fd, t_command_table *current,
			char **envp, t_memptr memptr)
{
	close_pipes(pipe_fd, current, memptr);
	if (current->valid_command == FALSE)
	{
		g_status_flag = current->current_g_status;
		final_clear_and_exit(memptr, envp, pipe_fd, current);
	}
	set_redirs(pipe_fd, &current, memptr);
	set_signal_during_processes_child();
	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else if (current->command_type == BUILTIN)
		execute_builtin(current, envp, memptr);
	final_clear_and_exit(memptr, envp, pipe_fd, current);
}

void	create_pid_array(int **pid_array, int process_num, t_memptr memptr)
{
	*pid_array = (int *)malloc(sizeof(int) * process_num);
	if (!(*pid_array))
		exit_error(MALLOC_ERROR, memptr, NULL);
}

void	process_forks(t_command_table **command_table, char **envp,
			int process_num, t_memptr memptr)
{
	int				**pipe_fd;
	int				*pid_array;
	int				i;
	t_command_table	*current;

	pipe_fd = create_pipes(process_num - 1, &memptr);
	current = *command_table;
	create_pid_array(&pid_array, process_num, memptr);
	i = 0;
	while (i++ < process_num)
	{
		current->pid = fork();
		if (current->pid < 0)
			exit_error(FORK_ERROR, memptr, NULL);
		else if (current->pid == 0)
		{
			free(pid_array);
			current->command_no = i;
			process_child(pipe_fd, current, envp, memptr);
		}
		else
			pid_array[i - 1] = current->pid;
		current = current->next;
	}
	process_parent(pipe_fd, process_num, pid_array, &memptr);
}
