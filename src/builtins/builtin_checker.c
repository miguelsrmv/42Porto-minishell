/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:24 by bmota-si          #+#    #+#             */
/*   Updated: 2024/03/11 15:07:48 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_checker(char **argv)
{
	if (!ft_strcmp(argv[0], "cd") || !ft_strcmp(argv[0], "pwd")
		|| !ft_strcmp(argv[0], "unset") || !ft_strcmp(argv[0], "export"))
	{
		if (argv[1] && argv[1][0] == '-' && argv[1][1] != '\0')
		{
			ft_putstr_fd("bash: invalid option\n", STDERR_FILENO);
			g_status_flag = 2;
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else if (!ft_strcmp(argv[0], "env"))
	{
		if (argv[1] && argv[1][0] == '-' && argv[1][1] != '\0')
		{
			ft_putstr_fd("bash: invalid option\n", STDERR_FILENO);
			g_status_flag = 125;
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
