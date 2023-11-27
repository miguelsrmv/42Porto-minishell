/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:30:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/27 21:08:13 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dquote_expansion(char **string, int *pos, char *quote_flag,
			t_memptr memptr)
{
	int	start_pos;
	int	end_pos;

	start_pos = *pos;
	end_pos = start_pos + take_out_outer_dquotes(string, pos, memptr);
	while ((*string)[*pos] && *pos <= end_pos)
	{
		if ((*string)[*pos] == '$' && (end_pos == start_pos))
		{
			expand_to_dollar_sign(string, pos, memptr);
			break ;
		}
		else if ((*string)[*pos] == '$' && !ft_isquote((*string)[(*pos) + 1]))
			expand_env_quotes(string, pos, &end_pos, memptr);
		else
			(*pos)++;
	}
	(*quote_flag) = '\0';
}

void	expand_env_quotes(char **string, int *start, int *end, t_memptr memptr)
{
	char	*substring;
	char	*expanded;
	int		limit;

	limit = (*start) + 1;
	while ((*string)[limit] && (*string)[limit] != '$'
			&& (*string)[limit] != SQUOTE && limit <= *end)
		limit++;
	substring = ft_substr((*string), (*start) + 1,
			limit - (*start) - 1);
	if (!substring)
		exit_error(MALLOC_ERROR, memptr);
	expanded = getenv(substring);
	if (!expanded)
		expanded = "";
	free(substring);
	if (concatenate(string, expanded, start, limit) == 1)
		exit_error(MALLOC_ERROR, memptr);
	(*end) = (*end) + ft_strlen(expanded) - (limit - (*start));
	(*start) = (*start) + ft_strlen(expanded);
}

// Desnecessário ?? Posso só passar à frente e dar break ? Incorporar $$ ??
void	expand_to_dollar_sign(char **string, int *start, t_memptr memptr)
{
	char	*expand;

	expand = (char *)malloc(sizeof(char) * 2);
	if (!expand)
		exit_error(MALLOC_ERROR, memptr);
	expand[0] = '$';
	expand[1] = '\0';
	if (concatenate(string, expand, start, *start + 1) == 1)
		exit_error(MALLOC_ERROR, memptr);
	(*start)++;
	free(expand);
}

int	take_out_outer_dquotes(char **string, int *start, t_memptr memptr)
{
	char	*unquoted_str;
	int		end;

	end = (*start) + 1;
	while ((*string)[end] != DQUOTE)
		end++;
	unquoted_str = ft_strndup(&(*string)[(*start) + 1], end - (*start) - 1);
	if (!unquoted_str)
		exit_error(MALLOC_ERROR, memptr);
	if (concatenate(string, unquoted_str, start, end + 1) == 1)
		exit_error(MALLOC_ERROR, memptr);
	free(unquoted_str);
	return (end - (*start) - 2);
}
