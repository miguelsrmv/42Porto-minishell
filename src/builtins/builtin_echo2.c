/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:49:43 by bmota-si          #+#    #+#             */
/*   Updated: 2023/12/19 17:42:19 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo(char **args, bool print_newline, int i)
{
	while (args[i])
	{
		if (!ft_printf("%s", args[i]))
			return (EXIT_FAILURE);
		if (ft_strlen(args[i]) != 0 && args[i + 1] != NULL)
			if (!ft_printf(" "))
				return (EXIT_FAILURE);
		i++;
	}
	if (print_newline)
		if (!ft_printf("\n"))
			return (EXIT_FAILURE);
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
		return (EXIT_SUCCESS);
	}
	return (-1);
}
