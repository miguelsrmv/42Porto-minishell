/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:49:43 by bmota-si          #+#    #+#             */
/*   Updated: 2024/03/04 17:50:09 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo(char **args, bool print_newline, int i)
{
	while (args[i])
	{
		if (ft_strcmp(args[i], "") == 0)
			;
		else if (!args[i])
		{
			ft_putstr_fd(args[i], STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else if (ft_strlen(args[i]) != 0 && args[i + 1] != NULL)
		{
			ft_putstr_fd(" ", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (print_newline)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_hifen(char *args, int *n, int i)
{
	if (args[i] == '-')
	{
		i++;
		while (args[i])
		{
			if (args[i] == 'n')
				*n = 0;
			else
				return (-1);
			i++;
		}
	}
	else
		return (-1);
	return (EXIT_SUCCESS);
}
