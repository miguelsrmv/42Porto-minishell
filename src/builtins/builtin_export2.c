/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:26 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/02 18:04:13 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_exit(char ***array, bool exit_status)
{
	ft_free_str_array(array);
	if (exit_status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_sort_loop(char **env_var_cpy, int i, int j)
{
	char	*temp;

	temp = NULL;
	while (env_var_cpy[i] != NULL && env_var_cpy[i + 1] != NULL)
	{
		j = i + 1;
		while (env_var_cpy[j] != NULL)
		{
			if (ft_strcmp(env_var_cpy[i], env_var_cpy[j]) > 0)
			{
				temp = ft_strdup(env_var_cpy[i]);
				if (temp == NULL)
				{
					ft_free_str_array(&env_var_cpy);
					return (EXIT_FAILURE);
				}
				ft_free_str(&env_var_cpy[i]);
				env_var_cpy[i] = env_var_cpy[j];
				env_var_cpy[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_print_with_value(char **env_var_cpy, int i)
{
	int	j;

	printf("declare -x ");
	j = 0;
	while (env_var_cpy[i][j])
	{
		if (&env_var_cpy[i][j] == ft_strchr(env_var_cpy[i], '='))
		{
			if (printf("%c\"", env_var_cpy[i][j++]) != 2)
				return (ft_export_exit(&env_var_cpy, EXIT_FAILURE));
		}
		else if (printf("%c", env_var_cpy[i][j++]) != 1)
			return (ft_export_exit(&env_var_cpy, EXIT_FAILURE));
	}
	if (printf("\"\n") != 2)
		return (ft_export_exit(&env_var_cpy, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	export_only(t_env *environment)
{
	char	**env_var_cpy;
	int		i;
	int		j;

	env_var_cpy = ft_str_arr_dup(environment->env_var);
	if (env_var_cpy == NULL)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	if (ft_sort_loop(env_var_cpy, i, j) == EXIT_FAILURE)
		return (ft_export_exit(&env_var_cpy, EXIT_FAILURE));
	while (env_var_cpy[i] != NULL)
	{
		if (ft_strchr(env_var_cpy[i], '=') != NULL)
		{
			if (ft_print_with_value(env_var_cpy, i)
				== EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (!printf("declare -x %s\n", env_var_cpy[i]))
			return (ft_export_exit(&env_var_cpy, EXIT_FAILURE));
		i++;
	}
	return (ft_export_exit(&env_var_cpy, EXIT_SUCCESS));
}
