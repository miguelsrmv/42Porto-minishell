/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:03 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 17:24:05 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int containsChar(const char *str, char target) 
{
	int i = 0;
	while (str[i] != '\0' && str[i] != target && !ft_isdigit(str[i]))
		i++;
	if(str[i] == target)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int		env(char **argv)
{
	int		i;
	t_env   *envv;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (EXIT_FAILURE);
	if (argv != NULL && argv[1] != NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (envv->env_var && envv->env_var[i] != NULL)
	{
		if(containsChar(envv->env_var[i], '=') == EXIT_SUCCESS)
		{
			if (ft_printf("%s\n", envv->env_var[i++]) == 0)
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
