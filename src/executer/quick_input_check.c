/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_input_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:32:44 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/23 21:56:26 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quick_input_check(t_command_table **command)
{
	int				i;
	t_command_table	*current;

	current = *command;
	while (current)
	{
		i = 0;
		while (current && current->full_input[i])
		{
			current->input_type = redir_check((current)->full_input[i++]);
			if (current->input_type == INVALID)
				break ;
			(current)->input_target = (current)->full_input[i++];
			if ((current)->input_type == INPUT)
			{
				if (access((current)->input_target, F_OK) != 0
					|| ft_strlen((current)->input_target) == 0)
				{
					current->command_type = NO_EXEC_INVALID_INPUT;
					break ;
				}
			}
		}
		current = current->next;
	}
}

void	input_end_process(t_command_table *command, t_memptr memptr)
{
	if (command->input_type == INVALID)
		non_exit_error(SYNTAX_ERROR, memptr, NULL);
	else if (command->input_type == INPUT)
	{
		if (ft_strlen(command->input_target) == 0)
			non_exit_error(EMPTY_ERROR, memptr, NULL);
		else
			non_exit_error(OPEN_ERROR, memptr, NULL);
	}
}
