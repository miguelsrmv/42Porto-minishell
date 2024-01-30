/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:45:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/30 14:27:13 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_bash_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\0')
		return (0);
	return (1);
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

void	advance_until_unquoted_whitespace(char *input, int *end,
			char quote_status)
{
	while ((!ft_isspace(input[*end]) || quote_status) && input[*end])
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
			while ((!ft_isspace(input[*end]) && !quote_status
					&& input[*end]))
			{
				(*end)++;
				if (ft_isquote(input[*end]))
					quote_status = input[*end];
				else if (input[*end] == '|'
					|| input[*end] == '<' || input[*end] == '>')
					return ;
			}
		}
	}
}
