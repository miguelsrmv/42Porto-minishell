/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_subfunc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/18 19:06:59 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concatenate(char **string, char *expanded_string, int *start, int end)
{
	char	*left;
	char	*right;

	left = ft_substr((*string), ft_isquote((*string)[0]),
			(*start) - ft_isquote((*string)[0]));
	right = ft_substr((*string),
			(*start) + end + ft_isquote((*string)[0]),
			ft_strlen(*string) - 2 * ft_isquote((*string)[0]));
	left = ft_strjoin(left, expanded_string);
	*string = ft_strjoin(left, right);
	free(left);
	free(right);
}

void	expand_env_no_quotes(char **string, int *start)
{
	(void)string;
	(void)start;
	return ;
}

void	expand_env_quotes(char **string, int *start, char *quote_flag)
{
	char	*substring;
	char	*expanded;
	int		end;

	end = (*start) + 1;
	while (is_valid_env_char ((*string)[end]))
		end++;
	substring = ft_substr((*string), (*start) + 1, end - 2);
	expanded = getenv(substring);
	free(substring);
	concatenate(string, expanded, start, end);
	(*start) = (*start) + ft_strlen(expanded) - 1;
	if (ft_isquote((*string)[(*start)]))
		(*quote_flag) = (*string)[(*start)];
	else
		(*quote_flag) = '\0';
}

void	take_out_after_quotes(char **string, int *start)
{
	(void)string;
	(void)start;
	return ;
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
	concatenate(string, expand, start, 0);
	(*start) = (*start) - ft_isquote((*string)[0]);
	free(expand);
}
