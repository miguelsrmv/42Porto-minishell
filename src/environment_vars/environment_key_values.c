/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_key_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:41:25 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/23 10:48:12 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_key(char *key, t_memptr *memptr)
{
	char	*result;
	int		key_len;

	key_len = ft_strlen(key);
	result = (char *)malloc((sizeof(char) * (key_len + 1)));
	if (!result)
	{
		free(key);
		exit_error(MALLOC_ERROR, *memptr, NULL);
	}
	ft_strlcpy(result, key, key_len + 1);
	result[key_len] = '\0';
	return (result);
}

char	*new_key_value(char *key, char *value, t_memptr *memptr)
{
	char	*result;
	int		key_len;
	int		value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	result = (char *)malloc((sizeof(char) * (key_len + 1 + value_len + 1)));
	if (!result)
	{
		free(key);
		exit_error(MALLOC_ERROR, *memptr, NULL);
	}
	ft_strlcpy(result, key, key_len + 1);
	result[key_len] = '=';
	ft_strlcpy(result + key_len + 1, value, value_len + 1);
	return (result);
}
