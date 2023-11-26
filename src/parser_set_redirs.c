/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_redirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:59:55 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/26 16:24:28 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_array(char **array, t_token *current, int i)
{
	array[i] = current->token;
	array[i + 1] = current->next->token;
	array[i + 2] = NULL;
	current->next->type = REDIRECT_TARGET;
}

int	count_redirect_targets(t_token *lexer_sublist)
{
	t_token	*current;
	int		i;

	i = 0;
	current = lexer_sublist;
	while (current && current->type != SEPARATOR)
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
	while (current && current->type != SEPARATOR)
	{
		if (current->type == REDIRECT && !ft_strchr(current->token, '\''
				&& !ft_strchr(current->token, '\"')))
		{
			if (ft_strchr(current->token, '>'))
			{
				fill_array((*command_table)->full_output, current,
					output_index);
				output_index = output_index + 2;
			}
			if (ft_strchr(current->token, '<'))
			{
				fill_array((*command_table)->full_input, current, input_index);
				input_index = input_index + 2;
			}
		}
		current = current->next;
	}
}

void	initialize_command_table(t_command_table **command_table)
{
	(*command_table)->cmd = NULL;
	(*command_table)->cmd_target = NULL;
	(*command_table)->command_type = EXECUTABLE;
	(*command_table)->full_input[0] = NULL;
	(*command_table)->input_target = NULL;
	(*command_table)->input_type = NONE;
	(*command_table)->input_fd = 0;
	(*command_table)->heredoc_buffer = NULL;
	(*command_table)->full_output[0] = NULL;
	(*command_table)->output_target = NULL;
	(*command_table)->output_type = NONE;
	(*command_table)->output_fd = 0;
	(*command_table)->pid = 0;
	(*command_table)->command_no = 0;
	(*command_table)->next = NULL;
}

void	set_full_redirections(t_token *lexer_sublist,
			t_command_table **command_table, t_memptr memptr)
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
		exit_error("Malloc error\n", memptr);
	initialize_command_table(command_table);
	fill_full_redir(current, command_table);
	i = 0;
	while ((*command_table)->full_input[i])
		i++;
	(*command_table)->full_input[i] = NULL;
	i = 0;
	while ((*command_table)->full_output[i])
		i++;
	(*command_table)->full_output[i] = NULL;
	check_heredocs(command_table);
}
