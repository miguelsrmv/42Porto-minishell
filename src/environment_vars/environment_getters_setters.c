/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_getters_setters.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:40:30 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/24 11:56:04 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	check_pwd_edge_case(char **envp, char *key, char *value,
		t_memptr *memptr)
{
	char	*cwd;
	int		oldpwd_position;

	oldpwd_position = find_env_var(envp, "OLDPWD");
	if (oldpwd_position < 0)
		return ;
	cwd = getcwd(NULL, 0);
	if (!ft_strcmp(key, "PWD") && ft_strcmp(cwd, value)
		&& !ft_strcmp(envp[oldpwd_position], "OLDPWD="))
		set_env_value(envp, "OLDPWD", NULL, memptr);
	free(cwd);
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
	if (!new_envp)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	if (value)
		new_envp[ft_tablen((void **)envp)] = new_key_value(key, value, memptr);
	else
		new_envp[ft_tablen((void **)envp)] = new_key(key, memptr);
	new_envp[ft_tablen((void **)envp) + 1] = NULL;
	ft_free_tabs((void **)memptr->envp);
	(memptr->envp) = new_envp;
	check_pwd_edge_case(new_envp, key, value, memptr);
}

void	set_env_value(char **envp, char *key, char *value, t_memptr *memptr)
{
	int	position;

	position = find_env_var(envp, key);
	if (position < 0)
		add_env_value(envp, key, value, memptr);
	else
	{
		free(envp[position]);
		if (value)
			envp[position] = new_key_value(key, value, memptr);
		else
			envp[position] = new_key(key, memptr);
	}
}

void	remove_env_value(char **envp, char *key, t_memptr *memptr)
{
	int		position;
	char	**new_envp;

	position = find_env_var(envp, key);
	if (position < 0)
		return ;
	else
	{
		new_envp = (char **)malloc(sizeof(char *) * (ft_tablen((void **)envp)
					+ 1));
		if (!new_envp)
			exit_error(MALLOC_ERROR, *memptr, NULL);
		cpy_old_vars_skip_position(envp, new_envp, position);
		ft_free_tabs((void **)(memptr->envp));
		(memptr->envp) = new_envp;
	}
}
