/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:31:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 09:23:48 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_substr_quotes(char const *s, unsigned int start, size_t len)
{
	char	*substring;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	substring = malloc(len * sizeof(char) + 1);
	if (!substring)
		return (NULL);
	ft_memcpy(substring, &s[start], len);
	substring[len] = '\0';
	return (substring);
}

static char	*get_token(const char *s, size_t *len)
{
	t_token			toks;
	char			*token;

	ft_memset(&toks, 0, sizeof(t_token));
	toks.i = 0;
	while (s[toks.i] && (toks.in_quote || !ft_isspace(s[toks.i])))
	{
		if (s[toks.i] == '\\' && (toks.quote_char != '\'' || !toks.in_quote))
		{
			toks.i += 2;
			if (!s[toks.i])
				break ;
		}
		else if (ft_isquote(s[toks.i])
			&& (ft_isspace(s[toks.i - 1]) || ft_isspace(s[toks.i + 1]))
			&& (!toks.in_quote || s[toks.i] == toks.quote_char))
		{
			toks.in_quote = !toks.in_quote;
			toks.quote_char = s[toks.i];
		}
		toks.i++;
	}
	*len = toks.i;
	token = ft_substr_quotes(s, 0, toks.i);
	return (token);
}

static int	get_token_count(const char *s)
{
	t_token	toks;

	ft_memset(&toks, 0, sizeof(t_token));
	toks.i = 0;
	while (s[toks.i])
	{
		if (s[toks.i] == '\\' && (toks.quote_char != '\'' || !toks.in_quote))
			toks.i += 2;
		else if (ft_isquote(s[toks.i])
			&& (ft_isspace(s[toks.i - 1]) || ft_isspace(s[toks.i + 1]))
			&& (!toks.in_quote || s[toks.i] == toks.quote_char))
		{
			toks.in_quote = !toks.in_quote;
			toks.quote_char = s[toks.i];
		}
		else if (!toks.in_quote && ft_isspace(s[toks.i]))
			toks.in_token = 0;
		else if (!toks.in_token)
		{
			toks.in_token = 1;
			toks.token_count++;
		}
		toks.i++;
	}
	return (toks.token_count);
}

static char	*get_next_token(const char **s, size_t *len)
{
	while (ft_isspace(**s))
		(*s)++;
	return (get_token(*s, len));
}

char	**readline_split(const char *s)
{
	char	**tokens;
	int		token_count;
	int		i;
	size_t	len;

	token_count = get_token_count(s);
	tokens = malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = -1;
	while (++i < token_count)
	{
		tokens[i] = get_next_token(&s, &len);
		if (!tokens[i])
		{
			while (i >= 0)
				free(tokens[i--]);
			free(tokens);
			return (NULL);
		}
		s += len;
	}
	tokens[token_count] = NULL;
	return (tokens);
}
