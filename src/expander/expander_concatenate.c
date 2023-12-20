/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_concatenate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 08:56:41 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	concatenate(char **string, char *expanded_string, int *start, int end)
{
	char	*left;
	char	*right;
	char	*temp;
	char	*stringcpy;

	left = NULL;
	right = NULL;
	temp = NULL;
	stringcpy = NULL;
	left = ft_substr((*string), 0, (*start));
	if (!left)
		return (free_concatenate(left, right, temp, stringcpy));
	right = ft_substr((*string), end, ft_strlen(*string) - end);
	if (!right)
		return (free_concatenate(left, right, temp, stringcpy));
	temp = ft_strjoin(left, expanded_string);
	if (!temp)
		return (free_concatenate(left, right, temp, stringcpy));
	stringcpy = (*string);
	(*string) = ft_strjoin(temp, right);
	if (!(*string))
		return (free_concatenate(left, right, temp, stringcpy));
	free_concatenate(left, right, temp, stringcpy);
	return (0);
}

int	free_concatenate(char *left, char *right, char *temp, char *stringcpy)
{
	if (left)
		free(left);
	if (right)
		free(right);
	if (temp)
		free(temp);
	if (stringcpy)
		free(stringcpy);
	return (1);
}
