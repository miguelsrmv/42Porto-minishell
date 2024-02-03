/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:03 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/03 10:24:36 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_char(const char *str, char target)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != target && !ft_isdigit(str[0]))
		i++;
	if (str[i] == target)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	env(char **argv)
{
	int		i;
	t_env	*envv;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (EXIT_FAILURE);
	if (argv[0] != NULL && argv[1] != NULL)
	{
		ft_printf("%s: %s: No such file or directory\n", argv[0], argv[1]);
		return (127);
	}
	i = 0;
	while (envv->env_var && envv->env_var[i] != NULL)
	{
		if (contains_char(envv->env_var[i], '=') == EXIT_SUCCESS)
		{
			if (ft_printf("%s\n", envv->env_var[i++]) == 0)
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
