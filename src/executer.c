/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/28 14:39:04 by mde-sa--         ###   ########.fr       */
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

int	**create_pipes(int **pipe_fd, int process_num)
{
	pipe_fd = (int **)malloc(sizeof(int *) * (process_num));
	if (!pipe_fd)
		return pipe_fd ; // Error
	process_num--;
	pipe_fd[process_num] = NULL;
	while (process_num--)
	{
		pipe_fd[process_num] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fd[process_num])
			return pipe_fd ;	// Error
		if (pipe(pipe_fd[process_num]) == -1)
			return pipe_fd ;	// Error
	}
	return (pipe_fd);
}

t_command_table	*create_processes(t_command_table **command_table,
		int command_no)
{
	int				i;
	t_command_table	*current;

	current = *command_table;
	i = 0;
	while (i < command_no)
	{
		current->pid = fork();
		if (current->pid == 0)
			return (NULL);
		current->command_no = i + 1;
		i++;
		if (i == command_no)
			break ;
		current = current->next;
	}
	return (current);
}

void	close_pipes(int **pipe_fd, t_command_table *current)
{
	int	i;

	i = 0;
	while (pipe_fd[i])
	{
		if (i != current->command_no - 2)
			close(pipe_fd[i][0]);
		if (i != current->command_no - 1)
			close(pipe_fd[i][1]);
		i++;
	}
}

void	prepare_processes(t_command_table **command_table)
{
	int				process_num;
	int				**pipe_fd;
	char			**path_list;
	t_command_table	*current;

	process_num = count_processes(command_table);
	pipe_fd = NULL;
	pipe_fd = create_pipes(pipe_fd, process_num);
	path_list = get_path_list();
	current = create_processes(command_table, process_num);
	close_pipes(pipe_fd, current);
	check_redirections(pipe_fd, &current);
	check_commands(&current, path_list);
	execve(current->cmd_target, current->cmd, NULL);
}
