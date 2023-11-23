/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:13:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/23 13:02:00 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *lexer_list)
{
	t_token	*current;

	current = lexer_list;
	while (current)
	{
		if (current->type == SEPARATOR)
		{
			if (!current->next || current->next->type == SEPARATOR)
				return (INVALID);
		}
		else if (current->type == REDIRECT)
		{
			if (!current->next || current->next->type == SEPARATOR
				|| current->next->type == REDIRECT)
				return (INVALID);
		}
		current = current->next;
	}
	return (VALID);
}

void	set_cmd(t_token *lexer_sublist, t_command_table **command_table,
				t_error error)
{
	t_token	*current;
	int		i;

	i = 0;
	current = lexer_sublist;
	while (current && current->type != SEPARATOR)
	{
		if (current->type == STRING)
			i++;
		current = current->next;
	}
	(*command_table)->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*command_table)->cmd)
		exit_error("Malloc error\n", error);
	i = 0;
	current = lexer_sublist;
	while (current && current->type != SEPARATOR)
	{
		if (current->type == STRING)
			(*command_table)->cmd[i++] = current->token;
		current = current->next;
	}
	(*command_table)->cmd[i] = NULL;
}

void	create_command_table(t_token *lexer_list,
					t_command_table **command_table, t_error error)
{
	t_token			*current_token;
	t_command_table	**current_table;

	current_token = lexer_list;
	current_table = command_table;
	while (current_token)
	{
		set_full_redirections(current_token, current_table, error);
		set_cmd(current_token, current_table, error);
		while (current_token && current_token->type != SEPARATOR)
			current_token = current_token->next;
		(*current_table)->next = NULL;
		if (current_token && current_token->type == SEPARATOR)
		{
			(*current_table)->next
				= (t_command_table *)malloc(sizeof(t_command_table));
			if (!(*current_table)->next)
				exit_error("Malloc error\n", error);
			current_table = &((*current_table)->next);
			current_token = current_token->next;
		}
	}
}

t_command_table	*parse_list(t_token *lexer_list, t_error error)
{
	t_command_table	*command_table;

	if (check_syntax(lexer_list) == INVALID)
		exit_error("Syntax error\n", error);
	command_table = (t_command_table *)malloc(sizeof(t_command_table));
	if (!command_table)
		exit_error("Malloc error\n", error);
	command_table->next = NULL;
	create_command_table(lexer_list, &command_table, error);
	return (command_table);
}
