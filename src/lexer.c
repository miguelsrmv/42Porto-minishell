/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:52:58 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/16 18:32:39 by mde-sa--         ###   ########.fr       */
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

// Ainda não funciona. Pretende recursivamente ler o input até que não estar sobre quotes
// Fazer com while loop em vez de recursivo??
char	*get_readline(char *prompt, int quote_status)
{
	char	*input;
	int		i;
	char	*temp;

	input = readline(prompt);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote_status = input[i];
		i++;
		if (input[i] == quote_status && quote_status != OUT_QUOTE)
		{
			quote_status = OUT_QUOTE;
			i++;
		}
	}
	if (quote_status != OUT_QUOTE)
	{
		temp = input;
		input = ft_strjoin(input, get_readline(">", quote_status));
		free(temp);
	}
	return (input);
}

// Antes de chamar esta funcao:
//// Confirmar que o input tem as quotes terminadas
////////caso contrario fazer strjoin com restante
//// Confirmar que o input não tem caractéres inválidos (definir quais?)
t_token	*read_readline()
{
	char	*input;
	t_token	*head;
	int		start;
	int		end;

	input = get_readline("minishell: ", OUT_QUOTE);
	if (!input)
		exit_error("Error: input is NULL\n");
	start = 0;
	end = 0;
	fill_in_list(input, &head, start, end);
	return (head);
}
