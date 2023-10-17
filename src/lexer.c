/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:52:58 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/17 09:42:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_list(char *input, t_token **head, int start, int end)
{	
	while (input[start])
	{
		while (ft_isspace(input[start]))
			start++;
		if (ft_isquote(input[start]))
			add_token_end(head, create_token
				(get_quote_token(input, &start, &end)));
		else if (is_valid_bash_char(input[start]))
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
//// Confirmar que o input não tem caractéres inválidos (definir quais?)
t_token	*read_readline(void)
{
	char	*input;
	t_token	*head;
	int		start;
	int		end;

	input = get_input("minishell: ");
	if (!input)
		exit_error("Error: input is NULL\n");
	start = 0;
	end = 0;
	fill_in_list(input, &head, start, end);
	return (head);
}
