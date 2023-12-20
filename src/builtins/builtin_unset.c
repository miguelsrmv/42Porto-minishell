/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:42 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/12 17:17:55 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_var(t_env *envv, int i)
{
	char	**split;
	char	*var;

	split = ft_split(envv->env_var[i], '=');
	if (split == NULL)
		return (NULL);
	var = ft_strdup(split[0]);
	ft_free_str_array(&split);
	return (var);
}

static void	ft_del_var(t_env *envv, int i)
{
	int	j;

	ft_free_str(&envv->env_var[i]);
	j = i;
	while (envv->env_var[j + 1])
	{
		envv->env_var[j] = envv->env_var[j + 1];
		j++;
		if (envv->env_var[j + 1] == NULL)
			envv->env_var[j] = NULL;
		i = ft_str_arr_len(envv->env_var);
	}
}

static int	ft_inner_loop(char **argv, t_env *envv, int i, int k)
{
	char	*var;

	var = NULL;
	if (ft_strcmp(envv->env_var[i], argv[k]) == 0
		|| ft_strcmp(envv->env_var[i], argv[k]) == 61)
	{
		var = ft_get_var(envv, i);
		if (var == NULL)
			return (EXIT_FAILURE);
		if (ft_strncmp(var, argv[k], ft_strlen(var) != 0)
			|| ft_strncmp(var, argv[k], ft_strlen(argv[k]) != 0))
		{
			ft_free_str(&var);
			return (2);
		}
		ft_del_var(envv, i);
	}
	ft_free_str(&var);
	return (EXIT_SUCCESS);
}

int	unset(char **argv)
{
	int		i;
	int		k;
	int		inner_out;
	t_env	*envv;

	k = 1;
	envv = get_envv();
	if (argv[k] == NULL)
		return (EXIT_SUCCESS);
	while (argv[k])
	{
		i = 0;
		while (envv->env_var[i])
		{
			inner_out = ft_inner_loop(argv, envv, i, k);
			if (inner_out == 2)
				break ;
			else if (inner_out == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		k++;
	}
	return (EXIT_SUCCESS);
}
