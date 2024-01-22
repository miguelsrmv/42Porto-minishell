/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:25:58 by bmota-si          #+#    #+#             */
/*   Updated: 2024/01/19 16:37:08 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_envv(envv);
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
