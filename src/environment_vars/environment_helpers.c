/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:59:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/21 16:42:42 by mde-sa--         ###   ########.fr       */
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
			if (old[j] == NULL)
				break ;
		}
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

void	update_oldpwd_location(char *new_dir, t_memptr *memptr)
{
	int		oldpwd_position;
	int		pwd_position;
	char	*old_pwd;

	oldpwd_position = find_env_var(memptr->envp, "OLDPWD");
	pwd_position = find_env_var(memptr->envp, "PWD");
	if (oldpwd_position >= 0)
	{
		if (pwd_position >= 0)
			old_pwd = ft_strjoin("OLDPWD=", get_env_value(memptr->envp, "PWD",
						memptr));
		else
			old_pwd = ft_strdup("OLDPWD=");
		if (!old_pwd)
		{
			free(new_dir);
			exit_error(MALLOC_ERROR, *memptr, NULL);
		}
		free(memptr->envp[oldpwd_position]);
		memptr->envp[oldpwd_position] = old_pwd;
	}
}

void	update_pwd_location(char *new_dir, t_memptr *memptr)
{
	int		pwd_position;
	char	*pwd;

	pwd_position = find_env_var(memptr->envp, "PWD");
	pwd = ft_strjoin("PWD=", new_dir);
	if (!pwd)
	{
		free(new_dir);
		exit_error(MALLOC_ERROR, *memptr, NULL);
	}
	free(memptr->envp[pwd_position]);
	memptr->envp[pwd_position] = pwd;
}
