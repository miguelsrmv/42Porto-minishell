/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:45:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/01 11:22:47 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_bash_char(char c)
{
	if (ft_isalnum(c)
		|| c == '_' || c == '/' || c == '.' || c == '-' || c == '~'
		|| c == '$')
		return (1);
	return (0);
}

char	*get_pipe_token(char *input, int *start, int *end)
{
	*end = *start;
	(*end)++;
	return (ft_strndup(&input[*start], (*end - *start)));
}



char	*get_redirect_token(char *input, int *start, int *end)
{
	char	*result;

	*end = *start;
	while (input[(*end)] == '>' || input[(*end)] == '<')
		(*end)++;
	result = ft_strndup(&input[*start], (*end - *start));
	return (result);
}

char	*get_string_token(char *input, int *start, int *end)
{
	char	*result;
	char	quote_status;

	*end = *start;
	quote_status = '\0';
	if (ft_isquote(input[*end]))
	{
		quote_status = input[*end];
		(*end)++;
	}
	advance_until_unquoted_whitespace(input, end, quote_status);
	result = ft_strndup(&input[*start], (*end - *start));
	return (result);
}

void	advance_until_unquoted_whitespace(char *input, int *end, char quote_status)
{
	while((!ft_isspace(input[*end]) || quote_status) && input[*end])
	{
		if (quote_status)
		{
			(*end)++;
			while ((input[*end] != quote_status) && input[*end])
				(*end)++;
		}
		quote_status = '\0';
		if (!quote_status)
		{
			while (!ft_isspace(input[*end]) && !quote_status && input[*end])
			{
				(*end)++;
				if (ft_isquote(input[*end]))
					quote_status = input[*end];
			}
		}
	}
}

/*
CODIGO VELHO!
char	*get_string_token(char *input, int *start, int *end)
{
	*end = *start;
	while (is_valid_bash_char(input[*end]) && input[*end])
		(*end)++;
	return (ft_strndup(&input[*start], (*end - *start)));
}

char	*get_quote_token(char *input, int *start, int *end)
{
	char	*result;
	char	quote;

	*end = *start + 1;
	quote = input[*start];
	while (input[(*end)] != quote && input[(*end)])
		(*end)++;
	(*end)++;
	result = ft_strndup(&input[*start], (*end - *start));
	return (result);
}

*/