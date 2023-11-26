/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_concatenate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/26 21:12:16 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	concatenate(char **string, char *expanded_string, int *start, int end)
{
	char	*left;
	char	*right;
	char	*temp;

	left = ft_substr((*string), (ft_isquote((*string)[0])), (*start));
	right = ft_substr((*string), end, ft_strlen(*string) - end);
	if (!left || !right)
		return (1);
	temp = ft_strjoin(left, expanded_string);
	*string = ft_strjoin(temp, right);
	if (!temp || !(*string))
		return (1);
	free(temp);
	free(left);
	free(right);
	return (0);
}
/* 
int	concatenate_for_squote(char **string, char *expanded_string,
	int *start, int end)
{
	char	*left;
	char	*right;
	char	*temp;

	left = ft_substr((*string), ft_isquote((*string)[0]), (*start));
	right = ft_substr((*string), end, ft_strlen(*string) - end);
	if (!left || !right)
		return (1);
	temp = ft_strjoin(left, expanded_string);
	*string = ft_strjoin(temp, right);
	if (!temp || !(*string))
		return (1);
	free(temp);
	free(left);
	free(right);
	return (0);
} */

int	concatenate_for_dquote(char **string, char *expanded_string,
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
	if (!left || !right)
		return (1);
	left = ft_strjoin(left, expanded_string);
	*string = ft_strjoin(left, right);
	if (!left || !(*string))
		return (1);
	free(left);
	free(right);
	return (0);
}
