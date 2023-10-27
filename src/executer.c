/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/27 21:05:19 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_command_table **command_table)
{
	t_command_table	*current;
	int				pipe_count;

	current = *command_table;
	pipe_count = 0;
	while (current)
	{
		if (current->next)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count);
}

int	**create_pipes(int **pipe_fd, int pipe_no)
{
	pipe_fd = (int **)malloc(sizeof(int *) * (pipe_no + 1));
	if (!pipe_fd)
		return pipe_fd ; // Error
	pipe_fd[pipe_no] = NULL;
	while ((pipe_no)--)
	{
		pipe_fd[pipe_no] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fd[pipe_no])
			return pipe_fd ;	// Error
		if (pipe(pipe_fd[pipe_no]) == -1)
			return pipe_fd ;	// Error
	}
	return (pipe_fd);
}

void	create_processes(t_command_table **command_table,
			t_command_table *current, int command_no)
{
	int	i;

	i = 0;
	while (i < command_no)
	{
		current->pid = fork();
		current->command_no = i + 1;
		if (current->pid == 0)
			return ;
		current = current->next;
		i++;
	}
}

void	close_pipes(int **pipe_fd, t_command_table *current)
{
	int	i;

	i = 0;
	while (pipe_fd[i])
	{
		if (i != current->command_no - 1)
			close(pipe_fd[i][0]);
		if (i != current->command_no)
			close(pipe_fd[i][1]);
		i++;
	}
}

void	prepare_processes(t_command_table **command_table)
{
	int				pipe_no;
	int				**pipe_fd;
	char			**path_list;
	t_command_table	*current;

	pipe_no = count_pipes(command_table);
	pipe_fd = create_pipes(pipe_fd, pipe_no + 1);
	path_list = get_path_list();
	current = *command_table;
	create_processes(command_table, current, pipe_no + 1);
	close_pipes(pipe_fd, current);
	check_redirections(pipe_fd, &current);
	check_commands(&current, path_list);
	execve(current->cmd_target, current->cmd, NULL);
}
