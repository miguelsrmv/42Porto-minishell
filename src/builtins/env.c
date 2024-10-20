/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:03 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 17:26:45 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **argv, char **envp)
{
	int	i;

	if (builtin_argument_checker(argv) == EXIT_FAILURE)
		return (g_status_flag);
	else if (argv[0] && (argv[1] && argv[1][0] != '-'))
	{
		ft_putstr_fd("env: No such file or directory\n", STDERR_FILENO);
		g_status_flag = 127;
		return (g_status_flag);
	}
	i = 0;
	while ((envp)[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", (envp)[i++]);
	}
	return (EXIT_SUCCESS);
}
