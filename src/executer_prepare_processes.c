/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_prepare_processes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/09 18:11:45 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	**create_pipes(int **pipe_fd, int pipe_num, t_memptr *memptr)
{
	if (!pipe_num)
		return (NULL);
	pipe_fd = (int **)malloc(sizeof(int *) * (pipe_num + 1));
	if (!pipe_fd)
		exit_error(MALLOC_ERROR, *memptr);
	pipe_fd[pipe_num] = NULL;
	memptr->pipe_fd = pipe_fd;
	while (pipe_num--)
	{
		pipe_fd[pipe_num] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fd[pipe_num])
			exit_error(MALLOC_ERROR, *memptr);
		if (pipe(pipe_fd[pipe_num]) == -1)
			exit_error(PIPE_ERROR, *memptr);
	}
	return (pipe_fd);
}

t_command_table	*create_processes(t_command_table **command_table,
		int command_no)
{
	int				i;
	t_command_table	*current;

	current = *command_table;
	i = 1;
	while (i < command_no)
	{
		current->pid = fork();
		current->command_no = i;
		if (current->pid != 0)
			return (current);
		i++;
		current = current->next;
	}
	current->command_no = i;
	return (current);
}

void	close_pipes(int **pipe_fd, t_command_table *current, t_memptr memptr)
{
	int	i;

	i = 0;
	if (!pipe_fd)
		return ;
	while (pipe_fd[i])
	{
		if (i != current->command_no - 2)
		{
			if (close(pipe_fd[i][0]) == -1)
				exit_error(CLOSE_ERROR, memptr);
		}
		if (i != current->command_no - 1)
		{
			if (close(pipe_fd[i][1]) == -1)
				exit_error(CLOSE_ERROR, memptr);
		}
		i++;
	}
}

void	prepare_processes(t_command_table **command_table, char **envp,
			t_memptr memptr)
{
	char			**path_list;
	int				pid;
	int				envp_pipe[2];

	path_list = get_path_list(&memptr);
	check_commands(command_table, path_list, memptr);
	ft_free_tabs((void **)path_list);
	if (pipe(envp_pipe) == -1)
		exit_error(PIPE_ERROR, memptr);
	pid = fork();
	if (pid < 0)
		exit_error(FORK_ERROR, memptr);
	else if (pid > 0)
		process_parent(command_table, envp, envp_pipe, memptr);
	else
		process_commands(command_table, envp, envp_pipe, memptr);
}

void	process_parent(t_command_table **command_table, char **envp,
			int *envp_pipe, t_memptr memptr)
{
	int	process_num;

	set_signal_during_processes_parent();
	process_num = count_processes(command_table);
	while (process_num--)
		wait(NULL);
	if ((*command_table)->command_type == BUILTIN && !(*command_table)->next)
		read_envp(envp_pipe, &envp, &memptr); // RECEBER TAMBÉM A EXIT STATUS!!
}
