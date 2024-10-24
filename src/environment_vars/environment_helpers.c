/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:59:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/24 11:56:22 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_old_vars_skip_position(char **old, char **dest, int index_to_skip)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[j] != NULL)
	{
		if (j == index_to_skip)
		{
			j++;
			continue ;
		}
		dest[i] = ft_strdup(old[j]);
		if (dest[i] == NULL)
		{
			while (i > 0)
				free(dest[--i]);
			dest[0] = NULL;
			return ;
		}
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

char	*get_env_value(char **envp, char *key, t_memptr *memptr)
{
	char	*value;
	int		position;

	(void)memptr;
	position = find_env_var(envp, key);
	if (position < 0)
		return (NULL);
	value = ft_strchr(envp[position], '=');
	if (value == NULL)
		return (NULL); // TODO: Check if this is the right behaviour
	return (value + 1);
}
