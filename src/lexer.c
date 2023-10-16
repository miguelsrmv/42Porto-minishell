/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:52:58 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/16 16:08:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_list(char *input, t_token **head, int start, int end)
{	
	while (input[start])
	{
		if ((end == 0 && ft_isquote(input[1]))
			|| (ft_isspace(input[start]) && ft_isquote(input[start + 1])))
			add_token_end(head,
				create_token(get_quote_token(input, &start, &end)));
		while (ft_isspace(input[start]))
			start++;
		if (is_valid_bash_char(input[start]))
			add_token_end(head, create_token
				(get_string_token(input, &start, &end)));
		else if (input[start] == '<' || input[start] == '>')
			add_token_end(head, create_token
				(get_redirect_token(input, &start, &end)));
		else if (input[start] == '|')
			add_token_end(head, create_token
				(get_pipe_token(input, &start, &end)));
		start = end;
	}
}

t_token	*read_readline(char *input)
{
	t_token	*head;
	int		start;
	int		end;

	start = 0;
	end = 0;
	fill_in_list(input, &head, start, end);
	return (head);
}
