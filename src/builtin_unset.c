/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:42 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 17:24:43 by mde-sa--         ###   ########.fr       */
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
    // Verifica se a variável de ambiente é igual ao argumento ou se o argumento é um sinal de igual
	if (ft_strcmp(envv->env_var[i], argv[k]) == 0
		|| ft_strcmp(envv->env_var[i], argv[k]) == 61)
	{
		// Obtém o valor atual da variável de ambiente
        var = ft_get_var(envv, i);
		if (var == NULL)
			return (EXIT_FAILURE);
        // Verifica se o valor da variável de ambiente corresponde ao argumento
		if (ft_strncmp(var, argv[k], ft_strlen(var) != 0)
			|| ft_strncmp(var, argv[k], ft_strlen(argv[k]) != 0))
		{
			// Libera a memória alocada para var e retorna 2
            ft_free_str(&var);
			return (2);
		}
        // Remove a variável de ambiente
		ft_del_var(envv, i);
	}
    // Libera a memória alocada para var e retorna EXIT_SUCCESS
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
