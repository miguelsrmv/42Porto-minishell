/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:59:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/21 15:46:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_old_vars_skip_position(char **old, char **dest, int index_to_skip)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[j])
	{
		if (j == index_to_skip)
			j++;
		dest[i] = old[j];
		i++;
		j++;
	}
	dest[i] = NULL;
}

void	cpy_old_vars_add_position_slot(char **old, char **dest,
		int index_to_skip)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[j])
	{
		if (i == index_to_skip)
			i++;
		dest[i] = old[j];
		i++;
		j++;
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
			&& (envp[i][ft_strlen(key)] == '='
				|| envp[i][ft_strlen(key)] == '\0'))
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
