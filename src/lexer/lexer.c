/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:52:58 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/29 12:55:32 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Aqui ponderar não ter Is_balid_bash_char mas sim simplesmente um else
// e tratar a validade dos caracteres no parser mais à frente
// Alternativamente, avisar logo aqui de invalid char e dar free e exit
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
		if (ft_isquote(input[start]))
			add_token_end(head, create_token
				(get_string_token(input, &start, &end), STRING, memptr));
		else if (is_valid_bash_char(input[start]))
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
	head = NULL;
	fill_in_list(input, &head, memptr);
	free(input);
	return (head);
}
