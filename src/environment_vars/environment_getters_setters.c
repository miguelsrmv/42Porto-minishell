/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_getters_setters.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:40:30 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/21 16:31:07 by mde-sa--         ###   ########.fr       */
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

void	add_env_value(char **envp, char *key, char *value, t_memptr *memptr)
{
	char	**new_envp;

	new_envp = (char **)malloc(sizeof(char *) * (ft_tablen((void **)envp) + 2));
	if (!new_envp)
	{
		free(key);
		exit_error(MALLOC_ERROR, *memptr, NULL);
	}
	cpy_old_vars_skip_position(envp, new_envp, -1);
	if (value)
		new_envp[ft_tablen((void **)envp)] = new_key_value(key, value, memptr);
	else
		new_envp[ft_tablen((void **)envp)] = new_key(key, memptr);
	new_envp[ft_tablen((void **)envp) + 1] = NULL;
	free(memptr->envp);
	(memptr->envp) = new_envp;
}

void	replace_env_value(char **arg_to_replace, char *key, char *value,
		t_memptr *memptr)
{
	free(*arg_to_replace);
	*arg_to_replace = new_key_value(key, value, memptr);
}

void	set_env_value(char **envp, char *key, char *value, t_memptr *memptr)
{
	int	position;

	position = find_env_var(envp, key);
	if (position < 0)
		add_env_value(envp, key, value, memptr);
	else
	{
		if (value)
			replace_env_value(&envp[position], key, value, memptr);
	}
}

void	remove_env_value(char **envp, char *key, t_memptr *memptr)
{
	int		position;
	char	**new_envp;

	position = find_env_var(envp, key);
	if (position < 0)
		return ; // TODO: UNSET IF KEY IS INVALID??
	else
	{
		new_envp = (char **)malloc(sizeof(char *) * (ft_tablen((void **)envp)
					+ 1));
		if (!new_envp)
			exit_error(MALLOC_ERROR, *memptr, NULL);
		cpy_old_vars_skip_position(envp, new_envp, position);
		free((memptr->envp)[position]);
		free(memptr->envp);
		(memptr->envp) = new_envp;
	}
}
