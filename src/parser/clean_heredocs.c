/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:38:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 10:02:15 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc_buffers(t_command_table **command_table)
{
	t_command_table	*current;

	current = *command_table;
	while (current)
	{
		if (current->heredoc_buffer)
		{
			if (access(current->heredoc_buffer, F_OK) == 0)
				unlink(current->heredoc_buffer);
			free(current->heredoc_buffer);
			current->heredoc_buffer = NULL;
		}
		current = current->next;
	}
}
