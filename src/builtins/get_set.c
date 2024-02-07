/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:30:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 16:26:09 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_env_var_value_utils(t_env *envv, char *var, char **value, int i)
{
	if (ft_strlen(*value) == 0 && ft_strcmp(var, "PWD") == 0)
	{
		if (ft_strlen(envv->pwd) == 0)
			*value = ft_calloc(1, sizeof (char));
		else
			*value = ft_strdup(envv->pwd);
	}
	else if (ft_strlen(*value) == 0 && ft_strcmp(var, "OLDPWD") == 0)
	{
		if (ft_strlen(envv->oldpwd) == 0)
			*value = ft_calloc(1, sizeof (char));
		else
			*value = ft_strdup(envv->oldpwd);
	}
	else if (envv->env_var[i] == NULL && *value == NULL)
		*value = ft_calloc(1, sizeof(char));
}

static t_env	*_get_envv(t_env *envv)
{
	static t_env	*static_envv = NULL;

	if (envv == NULL)
		return (static_envv);
	static_envv = envv;
	return (static_envv);
}

char	*get_env_var_value(t_env *envv, char *var)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	while (envv && envv->env_var && envv->env_var[i] != NULL)
	{
		if (ft_strcmp(var, envv->env_var[i]) == -61)
		{
			value = ft_strchr(envv->env_var[i++], '=') + 1;
			if (ft_strlen(value) == 0)
				value = ft_calloc(1, sizeof (char));
			else
				value = ft_strdup(value);
			break ;
		}
		else if (ft_strcmp(var, envv->env_var[i++]) == 0)
		{
			value = ft_calloc(1, sizeof (char));
			break ;
		}
	}
	if (!value)
		return (NULL);
	get_env_var_value_utils(envv, var, &value, i);
	return (value);
}

void	set_envv(t_env *envv)
{
	_get_envv(envv);
}

t_env	*get_envv(void)
{
	return (_get_envv(NULL));
}
