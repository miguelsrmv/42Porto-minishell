/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:03 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 11:23:37 by mde-sa--         ###   ########.fr       */
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

int	env2(char **argv, t_env *envv)
{
	(void)envv;
	if (ft_builtin_checker(argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((argv[0] != NULL && (argv[1] != NULL && argv[1][0] != '-')))
	{
		env_error_msg(argv[0]);
		g_status_flag = 127;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	env(char **argv)
{
	int		i;
	t_env	*envv;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (EXIT_FAILURE);
	if (env2(argv, envv) == EXIT_FAILURE)
		return (g_status_flag);
	i = 0;
	while (envv->env_var && envv->env_var[i] != NULL)
	{
		if (contains_char(envv->env_var[i], '=') == EXIT_SUCCESS)
		{
			if (printf("%s\n", envv->env_var[i++]) == 0)
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

void	env_error_msg(char *argv0)
{
	ft_putstr_fd(argv0, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}
