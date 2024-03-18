/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:52:58 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/18 14:47:39 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_list(char *input, t_token **head, t_memptr memptr)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (input[start])
	{
		while (ft_isspace(input[start]))
			start++;
		if (ft_isquote(input[start]) || is_valid_bash_char(input[start]))
			add_token_end(head, create_token
				(get_string_token(input, &start, &end), STRING, memptr));
		else if (input[start] == '<' || input[start] == '>')
			add_token_end(head, create_token
				(get_redirect_token(input, &start, &end), REDIRECT, memptr));
		else if (input[start] == '|')
			add_token_end(head, create_token
				(get_pipe_token(input, &start, &end), SEPARATOR, memptr));
		if (input[start])
			start = end;
	}
}

t_token	*read_readline(t_memptr memptr)
{
	char		*input;
	t_token		*head;

	input = NULL;
	input = get_input("minishell: ", memptr);
	if (!input)
		return (NULL);
	head = NULL;
	fill_in_list(input, &head, memptr);
	free(input);
	return (head);
}
