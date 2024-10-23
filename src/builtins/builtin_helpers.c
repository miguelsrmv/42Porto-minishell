/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:36:44 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 17:28:28 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	argument_is_invalid(char *argument)
{
	if (argument && argument[0] == '-' && argument[1] != '\0')
		return (true);
	return (false);
}

int	builtin_argument_checker(char **argv)
{
	if ((!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "unset")
			|| !ft_strcmp(argv[0], "export") || !ft_strcmp(argv[0], "env")
			|| !ft_strcmp(argv[0], "cd")) && argument_is_invalid(argv[1]))
	{
		if (!ft_strcmp(argv[0], "env"))
			g_status_flag = 125;
		else
			g_status_flag = 2;
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	error_message(char *message, int new_status_flag)
{
	ft_putstr_fd(message, STDERR_FILENO);
	g_status_flag = new_status_flag;
}
