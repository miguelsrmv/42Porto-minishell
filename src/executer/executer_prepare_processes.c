/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_prepare_processes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/25 15:28:47 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipes(int **pipe_fd, int pipe_num, t_memptr *memptr)
{
	if (!pipe_num)
		return (NULL);
	pipe_fd = (int **)malloc(sizeof(int *) * (pipe_num + 1));
	if (!pipe_fd)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	pipe_fd[pipe_num] = NULL;
	memptr->pipe_fd = pipe_fd;
	while (pipe_num--)
	{
		pipe_fd[pipe_num] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fd[pipe_num])
			exit_error(MALLOC_ERROR, *memptr, NULL);
		if (pipe(pipe_fd[pipe_num]) == -1)
			exit_error(PIPE_ERROR, *memptr, NULL);
	}
	return (pipe_fd);
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
				exit_error(CLOSE_ERROR, memptr, NULL);
		}
		if (i != current->command_no - 1)
		{
			if (close(pipe_fd[i][1]) == -1)
				exit_error(CLOSE_ERROR, memptr, NULL);
		}
		i++;
	}
}

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

int	check_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH:", 4) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	prepare_processes(t_command_table **command_table, char **envp,
			t_memptr *memptr)
{
	char			**path_list;
	int				process_num;

	quick_input_check(command_table);
	path_list = NULL;
	if (check_path(envp) == EXIT_SUCCESS)
	{
		path_list = get_path_list(memptr);
		check_commands(command_table, path_list, *memptr);
		ft_free_tabs((void **)path_list);
		memptr->path_list = NULL;
	}
	else
		check_commands(command_table, path_list, *memptr);
	process_num = count_processes(command_table);
	set_signal_during_processes_child();
	if (process_num == 1
		&& ((*command_table)->command_type == NO_EXEC_INVALID_INPUT
			|| (*command_table)->input_type == INVALID))
		input_end_process(*command_table, *memptr);
	else if (process_num == 1 && (*command_table)->command_type == BUILTIN)
		execute_single_builtin(*command_table, envp, *memptr);
	else
		process_forks(command_table, envp, process_num, *memptr);
}
