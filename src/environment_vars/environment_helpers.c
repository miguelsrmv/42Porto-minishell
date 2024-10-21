/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:59:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/21 12:38:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_key_value(char *key, char *value, t_memptr *memptr)
{
	char	*left;
	char	*result;

	left = ft_strjoin(key, "=");
	if (!left)
	{
		free(key);
		exit_error(MALLOC_ERROR, *memptr, NULL);
	}
	result = ft_strjoin(left, value);
	if (!result)
	{
		free(key);
		free(left);
		exit_error(MALLOC_ERROR, *memptr, NULL);
	}
	free(left);
	return (result);
}

void	cpy_old_vars_skip_position(char **old, char **dest, int index_to_skip)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[j])
	{
		if (i != index_to_skip)
		{
			dest[i] = old[j];
			j++;
		}
		i++;
	}
	dest[i] = NULL;
}

int	find_env_var(char **envp, char *key)
{
	int	i;

	if (!key || ft_strlen(key) == 0)
		return (-1); // TODO: Check if this is needed?
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& ft_strlen(envp[i]) > ft_strlen(key)
			&& envp[i][ft_strlen(key)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	find_env_var_insert_position(char **envp, char *key)
{
	int	i;
	int	key_length;

	i = 0;
	key_length = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], key_length) < 0)
			break ;
		i++;
	}
	return (i);
}
