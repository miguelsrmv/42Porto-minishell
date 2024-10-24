/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:38:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/24 12:05:09 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc_buffers(t_command_table **cmd_table)
{
	t_command_table	*current;

	current = *cmd_table;
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
