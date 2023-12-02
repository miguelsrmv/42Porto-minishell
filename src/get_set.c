/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:30:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/02 01:16:34 by bmota-si         ###   ########.fr       */
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
	get_env_var_value_utils(envv, var, &value, i);
	return (value);
}

t_env	*init_envv(char **envp)
{
	t_env	*envv;

	envv = ft_calloc(1, sizeof(t_env));
	if (envv != NULL && envp != NULL && *envp != NULL)
	{
		envv->envp = envp;
		envv->env_var = ft_str_arr_dup(envp);
		envv->pwd = get_env_var_value(envv, "PWD");
		envv->oldpwd = get_env_var_value(envv, "OLDPWD");
		if (envv->env_var != NULL && envv->pwd != NULL && envv->oldpwd != NULL)
			return (envv);
	}
	return (NULL);
}

void	free_envv(t_env *envv)
{
	envv->envp = NULL;
	ft_free_str_array(&envv->env_var);
	ft_free_str(&envv->pwd);
	ft_free_str(&envv->oldpwd);
	free(envv);
}

int	reinit_env_var(t_env *envv, char **argv)
{
	if (*envv->env_var == NULL)
	{
		envv->env_var = ft_realloc_str_arr(envv->env_var, 2);
		if (envv->env_var == NULL)
			return (EXIT_FAILURE);
		envv->env_var[0] = ft_strdup(argv[1]);
		if (envv->env_var[0] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	**_get_envp(char **envp, bool reset)
{
	static char	**static_envp = NULL;

	if (envp == NULL && !reset)
		return (static_envp);
	if (reset)
	{
		static_envp = NULL;
		return (NULL);
	}
	static_envp = envp;
	return (static_envp);
}

void	set_envp(char **envp)
{
	_get_envp(envp, false);
}


static t_env	*_get_envv(t_env *envv)
{
	static t_env	*static_envv = NULL;

	if (envv == NULL)
		return (static_envv);
	static_envv = envv;
	return (static_envv);
}

void	set_envv(t_env *envv)
{
	_get_envv(envv);
}

t_env	*get_envv(void)
{
	return (_get_envv(NULL));
}

char	*ft_strchr2(const char *s, int c)
{
	while (*s && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
	{
		s++;
		return ((char *)s);
	}
	return (0);
}

char	*get_echo_var(char *str)
{
	t_env 	*envv;
	char	*str2;
	int		i;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (NULL);
	i = 0;
	while (envv->env_var[i] != NULL)
	{
		if(containsStr(envv->env_var[i], str) == EXIT_SUCCESS)
		{
			str2 = ft_strdup(envv->env_var[i]);
			return(ft_strchr2(str2, '='));
		}
		else
			i++;
	}
	return (NULL);
}
