/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/25 12:27:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_pipes(t_command_table **command_table)
{
	t_command_table	*current;
	int				pipe_count;

	current = *command_table;
	pipe_count = 0;
	while (current)
	{
		if (current->type == PIPE)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count);
}

void	execute_commands(t_command_table **command_table)
{
	int	fork_no;
	t_command_table	*current;

	current = *command_table;
	check_input(command_table);
	check_output(command_table);
	check_commands(command_table);
	fork_no = count_pipes(command_table);
}
