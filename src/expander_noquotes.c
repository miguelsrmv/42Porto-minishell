/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_noquotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:30:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/20 14:49:13 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_expansion(char **string, int *pos, char *quote_flag)
{
	while ((*string)[*pos] && (*string)[*pos] != *quote_flag)
	{
		if ((*string)[*pos] == '$' && !(*string)[(*pos) + 1])
			(*pos)++;
		else if ((*string)[*pos] == '$' && ft_isquote((*string)[(*pos) + 1]))
			ansi_quoting(string, pos, quote_flag);
		else if ((*string)[*pos] == '$')
		{
			expand_env_no_quotes(string, pos, quote_flag);
			break ;
		}
		else if (ft_isquote((*string)[*pos]))
			break ;
		else
			(*pos)++;
	}
}

// Tirar quote flag?
void	ansi_quoting(char **string, int *start, char *quote_flag)
{
	char	*substring;
	int		end;

	end = (*start) + 2;
	while ((*string)[end] != ((*string)[*start + 1]))
		end++;
	substring = ft_substr((*string), (*start) + 2, end - (*start) - 2);
	concatenate(string, substring, start, end + 1);
	(*start) = (*start) + ft_strlen(substring);
	(void)(quote_flag);
}

// Tirar quote flag?
void	expand_env_no_quotes(char **string, int *start, char *quote_flag)
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
	(void)(quote_flag);
}

// Tirar quote flag?
void	take_out_after_quotes(char **string, int *start, char *quote_flag)
{
	char	*contracted_char;
	char	quote;
	int		end;

	end = (*start) + 1;
	quote = (*string)[end++];
	while ((*string)[end] != quote)
		end++;
	contracted_char = ft_substr((*string), (*start) + 2, end - (*start) - 2);
	concatenate(string, contracted_char, start, end + 1);
	(*start) = (*start) + 1 + ft_strlen(contracted_char);
	(void)(quote_flag);
}
