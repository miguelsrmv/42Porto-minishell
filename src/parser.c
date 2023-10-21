/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:13:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/21 20:11:14 by mde-sa--         ###   ########.fr       */
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

void	set_redirections(t_token *lexer_sublist,
					t_command_table **command_table)
{
	t_token	*current;

	current = lexer_sublist;
	(*command_table)->input = (char **)malloc(sizeof(char *) * 3);
	(*command_table)->output = (char **)malloc(sizeof(char *) * 3);
	if (!(*command_table)->input || !(*command_table)->output)
		exit_error("Malloc error\n");
	(*command_table)->input[0] = NULL;
	(*command_table)->output[0] = NULL;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIRECT && !ft_strchr(current->token, '\''
				&& !ft_strchr(current->token, '\"')))
		{
			if (ft_strchr(current->token, '>'))
			{
				(*command_table)->output[0] = current->token;
				(*command_table)->output[1] = current->next->token;
				(*command_table)->output[2] = NULL;
			}
			if (ft_strchr(current->token, '<'))
			{
				(*command_table)->input[0] = current->token;
				(*command_table)->input[1] = current->next->token;
				(*command_table)->input[2] = NULL;
			}
			current->next->type = REDIRECT_TARGET;
			current = current->next;
		}
		current = current->next;
	}
}

void	set_cmd(t_token *lexer_sublist, t_command_table **command_table)
{
	t_token	*current;
	int		i;

	i = 0;
	current = lexer_sublist;
	while (current && current->type != PIPE)
	{
		if (current->type == STRING)
			i++;
		current = current->next;
	}
	(*command_table)->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*command_table)->cmd)
		exit_error("Malloc error\n");
	i = 0;
	current = lexer_sublist;
	while (current && current->type != PIPE)
	{
		if (current->type == STRING)
			(*command_table)->cmd[i++] = current->token;
		current = current->next;
	}
	(*command_table)->cmd[i] = NULL;
}

void	create_command_table(t_token *lexer_list,
					t_command_table **command_table)
{
	t_token			*current_token;
	t_command_table	**current_table;

	current_token = lexer_list;
	current_table = command_table;
	while (current_token)
	{
		set_redirections(current_token, current_table);
		set_cmd(current_token, current_table);
		while (current_token && current_token->type != PIPE)
			current_token = current_token->next;
		if (current_token && current_token->type == PIPE)
		{
			(*current_table)->next
				= (t_command_table *)malloc(sizeof(t_command_table));
			if (!(*current_table)->next)
				exit_error("Malloc error\n");
			current_table = &((*current_table)->next);
			current_token = current_token->next;
		}
	}
}

t_command_table	*parse_list(t_token *lexer_list)
{
	t_command_table	*command_table;

	if (check_syntax(lexer_list) == INVALID)
		exit_error("Syntax error\n");
	command_table = (t_command_table *)malloc(sizeof(t_command_table));
	if (!command_table)
		exit_error("Malloc error\n");
	command_table->next = NULL;
	create_command_table(lexer_list, &command_table);
	return (command_table);
}
