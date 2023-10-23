/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:59:55 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/23 18:21:25 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_array(char **array, t_token *current,
			t_command_table **command_table, int i)
{
	array[i] = current->token;
	array[i + 1] = current->next->token;
	array[i + 2] = NULL;
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
				fill_array((*command_table)->output, current, command_table, 0);
			if (ft_strchr(current->token, '<'))
				fill_array((*command_table)->input, current, command_table, 0);
			current->next->type = REDIRECT_TARGET;
			current = current->next;
		}
		current = current->next;
	}
}

int	count_redirect_targets(t_token *lexer_sublist)
{
	t_token	*current;
	int		i;

	i = 0;
	current = lexer_sublist;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIRECT_TARGET)
			i++;
		current = current->next;
	}
	return (i);
}

void	fill_full_redir(t_token *current, t_command_table **command_table)
{
	int	input_i;
	int	output_i;

	input_i = 0;
	output_i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIRECT && !ft_strchr(current->token, '\''
				&& !ft_strchr(current->token, '\"')))
		{
			if (ft_strchr(current->token, '>'))
			{
				fill_array((*command_table)->full_o, current, command_table,
					output_i);
				output_i = output_i + 2;
			}
			if (ft_strchr(current->token, '<'))
			{
				fill_array((*command_table)->full_i, current, command_table,
					input_i);
				input_i = input_i + 2;
			}
		}
		current = current->next;
	}
}

void	set_full_redirections(t_token *lexer_sublist,
			t_command_table **command_table, t_error error)
{
	t_token	*current;
	int		i;

	current = lexer_sublist;
	(*command_table)->full_i = (char **)malloc(sizeof(char *)
			* (count_redirect_targets(lexer_sublist) * 2 + 1));
	(*command_table)->full_o = (char **)malloc(sizeof(char *)
			* (count_redirect_targets(lexer_sublist) * 2 + 1));
	if (!(*command_table)->full_i || !(*command_table)->full_o)
		exit_error("Malloc error\n", error);
	(*command_table)->full_i[0] = NULL;
	(*command_table)->full_o[0] = NULL;
	fill_full_redir(current, command_table);
	i = 0;
	while ((*command_table)->full_i[i])
		i++;
	(*command_table)->full_i[i] = NULL;
	i = 0;
	while ((*command_table)->full_o[i])
		i++;
	(*command_table)->full_o[i] = NULL;
}
