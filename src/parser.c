/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:13:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/17 13:16:17 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *lexer_list)
{
	t_token	*current;

	current = lexer_list;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->next || current->next->type == PIPE)
				return (INVALID);
		}
		else if (current->type == REDIRECT)
		{
			if (!current->next || current->next->type == PIPE
				|| current->next->type == REDIRECT)
				return (INVALID);
		}
		current = current->next;
	}
	return (VALID);
}

t_command_table	*parse_list(t_token *lexer_list)
{
	t_command_table	*command_table;

	if (check_syntax(lexer_list) == INVALID)
		exit_error("Syntax error\n");
	command_table = NULL;
	return (command_table);
}
