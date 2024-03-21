/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_childparent_processes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:43:18 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/21 19:25:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_parent(int **pipe_fd, int process_num, int *pid_array,
	t_memptr *memptr)
{
	int	i;

	i = 0;
	close_parent_pipes(pipe_fd, process_num, *memptr);
	while (i < process_num)
		waitpid(pid_array[i++], &g_status_flag, 0);
	if (WIFEXITED(g_status_flag))
		g_status_flag = WEXITSTATUS(g_status_flag);
	else if (WIFSIGNALED(g_status_flag))
		g_status_flag = WTERMSIG(g_status_flag) + 128;
	memptr->return_value = g_status_flag;
	free(pid_array);
	if (memptr->pipe_fd)
	{
		ft_free_tabs((void **)memptr->pipe_fd);
		memptr->pipe_fd = NULL;
	}
	clean_memory(*memptr);
}

void	process_child(int **pipe_fd, t_command_table *current,
			char **envp, t_memptr memptr)
{
	close_pipes(pipe_fd, current, memptr);
	if (current->command_type == NO_EXEC_INVALID_INPUT)
		non_exit_error(OPEN_ERROR, memptr, current->input_target);
	else if (check_redirections(pipe_fd, &current, memptr) != VALID)
		final_clear_and_exit(memptr, envp);
	if (current->command_type != EXECUTABLE && current->command_type != BUILTIN)
	{
		if (!current->cmd[0])
			g_status_flag = 0;
		final_clear_and_exit(memptr, envp);
	}
	if (current->command_type == EXECUTABLE)
	{
		current->cmd = remove_nullstrings(current->cmd, memptr);
		execve(current->cmd_target, current->cmd, envp);
	}
	else if (current->command_type == BUILTIN)
		execute_builtin(current, envp, memptr);
	final_clear_and_exit(memptr, envp);
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

	pipe_fd = NULL;
	pipe_fd = create_pipes(pipe_fd, process_num - 1, &memptr);
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
			process_fork_subfunc(pid_array, current, i);
			process_child(pipe_fd, current, envp, memptr);
		}
		else
			pid_array[i - 1] = current->pid;
		current = current->next;
	}
	process_parent(pipe_fd, process_num, pid_array, &memptr);
}

void	process_fork_subfunc(int *pid_array, t_command_table *current,
			int i)
{
	free(pid_array);
	current->command_no = i;
}
