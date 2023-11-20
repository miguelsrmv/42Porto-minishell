/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_subfunc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/20 18:52:56 by mde-sa--         ###   ########.fr       */
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

void	concatenate_for_dquote(char **string, char *expanded_string,
			int *start, int end)
{
	char	*left;
	char	*right;

	left = ft_substr((*string),
			ft_isdquote((*string)[0]),
			(*start) - ft_isdquote((*string)[(*start) - 1]));
	right = ft_substr((*string),
			end + 2 * ft_isdquote((*string)[(*start) - 1]),
			ft_strlen(*string) - end - ft_isdquote((*string)[(*start) - 1]));
	left = ft_strjoin(left, expanded_string);
	*string = ft_strjoin(left, right);
	free(left);
	free(right);
}