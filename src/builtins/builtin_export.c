/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/22 14:37:07 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_new(t_env *envv, t_export *exp, char **argv)
{
	if (envv->env_var[exp->i] == NULL)
	{
		envv->env_var = ft_realloc_str_arr
			(envv->env_var, ft_str_arr_len(envv->env_var) + 1);
		envv->env_var[exp->i] = ft_strdup(argv[exp->j]);
		ft_free_str(&exp->var);
		if (envv->env_var == NULL || envv->env_var[exp->i] == NULL)
			return (EXIT_FAILURE);
		if (export_special(envv, exp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (2);
	}
	return (EXIT_SUCCESS);
}

void	ft_split_var(t_export *exp, char **argv)
{
	char	**var_split;

	var_split = ft_split(argv[exp->j], '=');
	if (var_split == NULL)
		exp->var = NULL;
	else
	{
		exp->var = ft_strdup(var_split[0]);
		ft_free_str_array(&var_split);
	}
}

int	ft_export_loop(t_env *envv, t_export *exp, char **argv)
{
	exp->j = 1;
	while (argv[exp->j] != NULL)
	{
		if (check_argv_var(argv[exp->j]) == EXIT_SUCCESS)
		{
			ft_split_var(exp, argv);
			if (exp->var == NULL)
				return (EXIT_FAILURE);
			exp->i = 0;
			if (export_wd(envv, exp, argv) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (ft_export_loop2(envv, exp, argv, envv->env_var[exp->i]))
				return (EXIT_FAILURE);
		}
		else
			return (EXIT_FAILURE);
			//g_status_flag = 1;
		exp->j++;
	}
	return (EXIT_SUCCESS);
}

int	ft_export_loop2(t_env *envv, t_export *exp, char **argv, char *str)
{
	int	check;

	while (str)
	{
		check = ft_export_found(envv, exp, argv);
		if (check == 2)
			break ;
		else if (check == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export(char **argv)
{
	t_export	*exp;
	t_env		*envv;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (EXIT_FAILURE);
	if (argv[1] == NULL)
		export_only(envv);
	else
	{
		exp = ft_calloc(1, sizeof(t_export));
		if (exp == NULL)
			return (EXIT_FAILURE);
		if (export2(argv, exp, envv) == EXIT_SUCCESS)
			ft_free((void *)&exp);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
