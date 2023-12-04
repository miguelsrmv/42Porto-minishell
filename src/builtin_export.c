/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/04 18:08:11 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_new(t_env *envv, t_export *exp, char **argv)
{
	if(check_argv_var(argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (envv->env_var[exp->i] == NULL)
	{
		envv->env_var = ft_realloc_str_arr
			(envv->env_var, ft_str_arr_len(envv->env_var) + 1);
		envv->env_var[exp->i] = ft_strdup(argv[exp->j++]);
		ft_free_str(&exp->var);
		if (envv->env_var == NULL || envv->env_var[exp->i] == NULL)
			return (EXIT_FAILURE);
		if (export_special(envv, exp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (2);
	}
	return (EXIT_SUCCESS);
}

static int	ft_export_found(t_env *envv, t_export *exp, char **argv)
{
	int	check;

	if (ft_strcmp(envv->env_var[exp->i], exp->var) == 0
		|| ft_strcmp(envv->env_var[exp->i], exp->var) == 61)
	{
		ft_free_str(&envv->env_var[exp->i]);
		envv->env_var[exp->i] = ft_strdup(argv[exp->j++]);
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

static void	ft_split_var(t_export *exp, char **argv)
{
	char	**var_split;

	// Divide a string no índice exp->j no array argv usando '=' como delimitador
	var_split = ft_split(argv[exp->j], '=');
	// Verifica se a divisão foi bem-sucedida
	if (var_split == NULL)
		exp->var = NULL; // Define exp->var como NULL se a divisão falhar
	else
	{
		// Se a divisão for bem-sucedida, duplica a primeira parte (antes do '=')
		exp->var = ft_strdup(var_split[0]);
		// Libera a memória alocada para o array dividido
		ft_free_str_array(&var_split);
	}
}

static int	ft_export_loop(t_env *envv, t_export *exp, char **argv)
{
	int		check;

	exp->j = 1;
	while (argv[exp->j])
	{
		ft_split_var(exp, argv);
		if (exp->var == NULL)
			return (EXIT_FAILURE);
		exp->i = 0;
		if (export_wd(envv, exp, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		while (envv->env_var[exp->i])
		{
			check = ft_export_found(envv, exp, argv);
			if (check == 2)
				break ;
			else if (check == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int     export(char **argv)
{
    t_export    *exp;
    t_env       *envv;

    envv = get_envv();
    if (envv == NULL || envv->env_var == NULL)
		return (EXIT_FAILURE);
    if (argv[1] == NULL)
		export_only(envv);
    else if (export_input_error(argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
    else
	{
		exp = ft_calloc(1, sizeof(t_export));
		if (exp == NULL)
			return (EXIT_FAILURE);
		if (reinit_env_var(envv, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_export_loop(envv, exp, argv) == EXIT_FAILURE)
		{
			ft_free((void *)&exp);
			return (EXIT_FAILURE);
		}
		ft_free((void *)&exp);
	}
    return (EXIT_SUCCESS);
}

