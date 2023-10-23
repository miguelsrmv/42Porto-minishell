/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:59:55 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/23 21:15:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_array(char **array, t_token *current,
			t_command_table **command_table, int i)
{
	array[i] = current->token;
	array[i + 1] = current->next->token;
	array[i + 2] = NULL;
	current->next->type = REDIRECT_TARGET;
}

void	set_final_redirection(t_command_table **command_table, t_error error)
{
	int	i;

	(*command_table)->input = (char **)malloc(sizeof(char *) * 3);
	(*command_table)->output = (char **)malloc(sizeof(char *) * 3);
	if (!(*command_table)->input || !(*command_table)->output)
		exit_error("Malloc error\n", error);
	(*command_table)->input[0] = NULL;
	(*command_table)->output[0] = NULL;
	i = 0;
	while ((*command_table)->full_input[i])
		i++;
	(*command_table)->input[0] = (*command_table)->full_input[i - 2];
	(*command_table)->input[1] = (*command_table)->full_input[i - 1];
	(*command_table)->input[2] = NULL;
	i = 0;
	while ((*command_table)->full_output[i])
		i++;
	(*command_table)->output[0] = (*command_table)->full_output[i - 2];
	(*command_table)->output[1] = (*command_table)->full_output[i - 1];
	(*command_table)->output[2] = NULL;
}

int	count_redirect_targets(t_token *lexer_sublist)
{
	t_token	*current;
	int		i;

	i = 0;
	current = lexer_sublist;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIRECT)
			i++;
		current = current->next;
	}
	return (i);
}

void	fill_full_redir(t_token *current, t_command_table **command_table)
{
	int	input_index;
	int	output_index;

	input_index = 0;
	output_index = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIRECT && !ft_strchr(current->token, '\''
				&& !ft_strchr(current->token, '\"')))
		{
			if (ft_strchr(current->token, '>'))
			{
				fill_array((*command_table)->full_output, current,
					command_table, output_index);
				output_index = output_index + 2;
			}
			if (ft_strchr(current->token, '<'))
			{
				fill_array((*command_table)->full_input, current,
					command_table, input_index);
				input_index = input_index + 2;
			}
		}
		current = current->next;
	}
}

void	set_full_redirections(t_token *lexer_sublist,
			t_command_table **command_table, t_error error)
{
	t_token	*current;
	int		total_redirects;
	int		i;

	current = lexer_sublist;
	total_redirects = count_redirect_targets(lexer_sublist);
	(*command_table)->full_input = (char **)malloc(sizeof(char *)
			* (total_redirects * 2 + 1));
	(*command_table)->full_output = (char **)malloc(sizeof(char *)
			* (total_redirects * 2 + 1));
	if (!(*command_table)->full_input || !(*command_table)->full_output)
		exit_error("Malloc error\n", error);
	(*command_table)->full_input[0] = NULL;
	(*command_table)->full_output[0] = NULL;
	fill_full_redir(current, command_table);
	i = 0;
	while ((*command_table)->full_input[i])
		i++;
	(*command_table)->full_input[i] = NULL;
	i = 0;
	while ((*command_table)->full_output[i])
		i++;
	(*command_table)->full_output[i] = NULL;
}
