/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:30:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/20 14:48:07 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dquote_expansion(char **string, int *pos, char *quote_flag)
{
	int	original_pos;

	original_pos = *pos;
	take_out_outer_quotes(string, pos, quote_flag);
	(*pos) = original_pos;
	while ((*string)[*pos])
	{
		if ((*string)[*pos] == '$' && !(*string)[(*pos) + 1])
		{
			expand_to_dollar_sign(string, pos, quote_flag);
			break ;
		}
		else if ((*string)[*pos] == '$' && !ft_isquote((*string)[(*pos) + 1]))
			expand_env_quotes(string, pos, quote_flag);
		else
			(*pos)++;
	}
}

void	expand_env_quotes(char **string, int *start, char *quote_flag)
{
	char	*substring;
	char	*expanded;
	int		end;

	end = (*start) + 1;
	while (is_valid_env_char ((*string)[end]))
		end++;
	substring = ft_substr((*string), (*start) + 1, end - (*start) - 1);
	expanded = getenv(substring);
	if (!expanded)
		expanded = "";
	free(substring);
	concatenate(string, expanded, start, end);
	(*start) = (*start) + ft_strlen(expanded);
	(*quote_flag) = '\0';
}

void	expand_to_dollar_sign(char **string, int *start, char *quote_flag)
{
	char	*expand;

	expand = (char *)malloc(sizeof(char) * 2);
	if (!expand)
		return ;
	expand[0] = '$';
	expand[1] = '\0';
	concatenate(string, expand, start, 1);
	(*start) = (*start) - ft_isquote((*string)[0]);
	free(expand);
	(*quote_flag) = '\0';
}
