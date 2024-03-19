/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_input_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:32:44 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 10:02:06 by mde-sa--         ###   ########.fr       */
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
		while ((current)->full_input[i])
		{
			if (current->command_type == NO_EXEC_INVALID_INPUT)
				break ;
			if (redir_check((current)->full_input[i]) != INVALID)
				current->input_type = redir_check((current)->full_input[i++]);
			else
				current->command_type = NO_EXEC_INVALID_INPUT;
			(current)->input_target = (current)->full_input[i++];
			if (((current)->input_type == INPUT)
				&& access((current)->input_target, F_OK) != 0)
				current->command_type = NO_EXEC_INVALID_INPUT;
			else if (((current)->input_type == INPUT)
				&& ft_strlen((current)->input_target) == 0)
				current->command_type = NO_EXEC_INVALID_INPUT;
		}
		current = current->next;
	}
}
