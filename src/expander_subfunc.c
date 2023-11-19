/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_subfunc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/19 17:14:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concatenate(char **string, char *expanded_string, int *start, int end)
{
	char	*left;
	char	*right;

	left = ft_substr((*string),
			ft_isquote((*string)[0]),
			(*start) - ft_isquote((*string)[(*start) - 1]));
	right = ft_substr((*string),
			end + 2 * ft_isquote((*string)[(*start) - 1]),
			ft_strlen(*string) - end - ft_isquote((*string)[(*start) - 1]));
	left = ft_strjoin(left, expanded_string);
	*string = ft_strjoin(left, right);
	free(left);
	free(right);
}

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
	if (ft_isquote((*string)[(*start)]))
		(*quote_flag) = (*string)[(*start)];
	else
	{
		(*quote_flag) = '\0';
		(*start)--;
	}
}

// Unir funções pq na linha 68 pode-se trocar por ft_isquote(quote_flag) ? 
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
	concatenate(string, expanded, start, end - 1);
	(*start) = (*start) - 1 + ft_strlen(expanded);
	if (ft_isquote((*string)[(*start)]))
		(*quote_flag) = (*string)[(*start)];
	else
	{
		(*quote_flag) = '\0';
		(*start)--;
	}
}

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
	if (ft_isquote((*string)[(*start)]))
		(*quote_flag) = (*string)[(*start)];
	else
	{
		(*quote_flag) = '\0';
		(*start)--;
	}
}

void	take_out_quote_flag(char **string, int *start)
{
	(void)string;
	(void)start;
	return ;
}

void	expand_to_dollar_sign(char **string, int *start)
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
}
