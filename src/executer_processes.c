/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 14:53:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_processes(t_command_table **command_table)
{
	t_command_table	*current;
	int				processes_count;

	current = *command_table;
	processes_count = 1;
	while (current)
	{
		if (current->next)
			processes_count++;
		current = current->next;
	}
	return (processes_count);
}

int	**create_pipes(int **pipe_fd, int process_num, t_memptr *memptr)
{
	pipe_fd = (int **)malloc(sizeof(int *) * (process_num));
	if (!pipe_fd)
		exit_error(MALLOC_ERROR, *memptr);
	process_num--;
	pipe_fd[process_num] = NULL;
	memptr->pipe_fd = pipe_fd;
	while (process_num--)
	{
		pipe_fd[process_num] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fd[process_num])
			exit_error(MALLOC_ERROR, *memptr);
		if (pipe(pipe_fd[process_num]) == -1)
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
	int				process_num;
	int				pid;
	int				**pipe_fd;
	char			**path_list;
	t_command_table	*current;

	process_num = count_processes(command_table);
	pid = fork();
	if (pid == -1)
		exit_error(FORK_ERROR, memptr);
	else if (pid > 0)
	{
		while (process_num--)
			wait(NULL);
		return ;
	}
	path_list = get_path_list(&memptr);
	check_commands(command_table, path_list, memptr);
	pipe_fd = NULL;
	pipe_fd = create_pipes(pipe_fd, process_num, &memptr);
	current = create_processes(command_table, process_num);
	close_pipes(pipe_fd, current, memptr);
	check_redirections(pipe_fd, &current, memptr);	// Meter error management aqui! Expandir tb o ?$
	execute(current, envp);
}
