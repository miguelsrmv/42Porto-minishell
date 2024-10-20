/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_getters_setters.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:40:30 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 18:02:31 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

void	set_env_value(char ***envp, char *key, char *value, t_memptr *memptr)
{
	int		position;
	char	**new_envp;

	position = find_env_var(*envp, key);
	if (position < 0)
	{
		new_envp = (char **)malloc(sizeof(char *) * (ft_tablen((void **)*envp)
					+ 2));
		if (!new_envp)
			exit_error(MALLOC_ERROR, *memptr, NULL);
		cpy_old_vars_skip_position(*envp, new_envp, -1);
		new_envp[ft_tablen((void **)*envp)] = new_key_value(key, value, memptr);
		new_envp[ft_tablen((void **)*envp) + 1] = NULL;
		free(*envp);
		(memptr->envp) = new_envp;
	}
	else
	{
		free((*envp)[position]);
		(*envp)[position] = new_key_value(key, value, memptr);
	}
}

void	remove_env_value(char ***envp, char *key, t_memptr *memptr)
{
	int		position;
	char	**new_envp;

	position = find_env_var(*envp, key);
	if (position < 0)
		return ; // TODO: UNSET IF KEY IS INVALID??
	else
	{
		new_envp = (char **)malloc(sizeof(char *) * (ft_tablen((void **)*envp)
					+ 1));
		if (!new_envp)
			exit_error(MALLOC_ERROR, *memptr, NULL);
		cpy_old_vars_skip_position(*envp, new_envp, position);
		free((*envp)[position]);
		free(*envp);
		(memptr->envp) = new_envp;
	}
}
