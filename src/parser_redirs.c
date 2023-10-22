/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:59:55 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/22 14:03:00 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_input(t_token *current, t_command_table **command_table)
{
	(*command_table)->input[0] = current->token;
	(*command_table)->input[1] = current->next->token;
	(*command_table)->input[2] = NULL;
}

void	fill_output(t_token *current, t_command_table **command_table)
{
	(*command_table)->output[0] = current->token;
	(*command_table)->output[1] = current->next->token;
	(*command_table)->output[2] = NULL;
}

void	set_redirections(t_token *lexer_sublist,
			t_command_table **command_table, t_error error)
{
	t_token	*current;

	current = lexer_sublist;
	(*command_table)->input = (char **)malloc(sizeof(char *) * 3);
	(*command_table)->output = (char **)malloc(sizeof(char *) * 3);
	if (!(*command_table)->input || !(*command_table)->output)
		exit_error("Malloc error\n", error);
	(*command_table)->input[0] = NULL;
	(*command_table)->output[0] = NULL;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIRECT && !ft_strchr(current->token, '\''
				&& !ft_strchr(current->token, '\"')))
		{
			if (ft_strchr(current->token, '>'))
				fill_output(current, command_table);
			if (ft_strchr(current->token, '<'))
				fill_input(current, command_table);
			current->next->type = REDIRECT_TARGET;
			current = current->next;
		}
		current = current->next;
	}
}
