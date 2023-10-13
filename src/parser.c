/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:42:53 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/13 22:09:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_tokens(const char *s)
{
	char	**tokens;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	tokens = malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!tokens)
		return (NULL);
	while (s[i])
	{
		tokens[len] = get_word(&s[i], &i);
		len++;
	}
	tokens[len] = NULL;
	return (tokens);
}

char	**readline_split(const char *s)
{
	char	**tokens;

	tokens = get_tokens(s);
	return (tokens);
}
