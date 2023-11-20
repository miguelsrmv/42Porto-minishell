/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:30:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/20 18:59:42 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dquote_expansion(char **string, int *pos, char *quote_flag)
{
	int	start_pos;
	int	end_pos;

	start_pos = *pos;
	end_pos = take_out_outer_dquotes(string, *pos);
	(void)start_pos;
	(void)end_pos;
	while ((*string)[*pos] && *pos < end_pos)
	{
		if ((*string)[*pos] == '$' && end_pos == start_pos + 1)
		{
			expand_to_dollar_sign(string, pos, quote_flag);						// Desnecessário ?? Posso só passar à frente e dar break ?
			break ;
		}
		else if ((*string)[*pos] == '$' && !ft_isquote((*string)[(*pos) + 1]))
			expand_env_quotes(string, pos, quote_flag);
		else
			(*pos)++;
	}
	(*quote_flag) = '\0';

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
	concatenate_for_dquote(string, expanded, start, end);
	(void)(quote_flag);
}

void	expand_to_dollar_sign(char **string, int *start, char *quote_flag)
{
	char	*expand;

	expand = (char *)malloc(sizeof(char) * 2);
	if (!expand)
		return ;
	expand[0] = '$';
	expand[1] = '\0';
	concatenate(string, expand, start, *start + 1);
	(*start)++;
	free(expand);
	(void)(quote_flag);
}

int	take_out_outer_dquotes(char **string, int start)
{
	int		end;
	char	*unquoted_char;

	end = start + 1;
	while ((*string)[end] != dquote)
		end++;
	(end)--;
	(start)++;
	unquoted_char = ft_substr((*string), start, end - start + 1);
	concatenate(string, unquoted_char, &start, end);
	return (end);
}

/*
void	take_out_first_dquote(char **string, int *start, char *quote_flag)
{
	char	*unquoted_char;
	int		end;

	end = (*start) + 1;
	while ((*string)[end] != *quote_flag)
		end++;
	unquoted_char = ft_substr((*string), (*start) + 1, end - (*start));
	(*start)++;
	concatenate(string, unquoted_char, start, end - 1);
	(*start)--;
	(*quote_flag) = '\0';

}

void	take_out_last_dquote(char **string, int start, char *quote_flag)
{
	char	*unquoted_char;
	int		end;

	end = start + 1;
	while ((*string)[end] != dquote)
		end++;
	unquoted_char = ft_substr((*string), (start), end - (start));
	concatenate(string, unquoted_char, &start, end + 1);
	(void)(quote_flag);
}
*/