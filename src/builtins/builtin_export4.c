/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:34 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/18 11:30:50 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_error_loop(char **var, char **argv)
{
	int	j;

	j = 0;
	while ((*var)[j] != '\0')
	{
		if (ft_isalnum((*var)[j]) == 0 && (*var)[j] != '_')
		{
			ft_fprintf(2, "export: %s: not a valid identifier\n", argv[1]);
			ft_free_str(var);
			return (EXIT_FAILURE);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int	export_input_error(char **argv)
{
	char	**split;
	char	*var;
	int		i;

	i = 1;
	var = NULL;
	while (argv && argv[i])
	{
		split = ft_split(argv[i], '=');
		if (split == NULL)
			return (EXIT_FAILURE);
		if (split[0])
		{
			var = ft_strdup(split[0]);
			ft_free_str_array(&split);
		}
		if (var == NULL)
			return (EXIT_FAILURE);
		if (export_error_loop(&var, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
		ft_free_str(&var);
	}
	return (EXIT_SUCCESS);
}

int	check_argv_var(char *argv)
{
	int		i;

	i = 0;
	if (!ft_isalpha(argv[0]) && argv[0] != '_' && argv[0] != '|')
	{
		ft_printf("minishell: '%s' Not a valid identifier!\n", argv);
		return (EXIT_FAILURE);
	}
	if ((argv[0] == '_' && (argv[1] == '\0' || argv[1] == '=')))
		return (EXIT_FAILURE);
	while (argv[i] != '\0' && argv[i] != '=')
	{
		if (argv[i] == '-' || argv[i] == '+')
		{
			ft_printf("minishell: '%s' Not a valid identifier!\n", argv);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export2(char **argv, t_export *exp, t_env *envv)
{
	if (reinit_env_var(envv, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_export_loop(envv, exp, argv) == EXIT_FAILURE)
	{
		ft_free((void *)&exp);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_export_found(t_env *envv, t_export *exp, char **argv)
{
	int	check;

	if (ft_strcmp(envv->env_var[exp->i], exp->var) == 0
		|| ft_strcmp(envv->env_var[exp->i], exp->var) == 61)
	{
		ft_free_str(&envv->env_var[exp->i]);
		envv->env_var[exp->i] = ft_strdup(argv[exp->j]);
		ft_free_str(&exp->var);
		if (envv->env_var[exp->i] == NULL)
			return (EXIT_FAILURE);
		exp->i++;
		return (2);
	}
	else
	{
		exp->i++;
		check = ft_export_new(envv, exp, argv);
		if (check == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (check == 2)
			return (2);
	}
	return (EXIT_SUCCESS);
}
