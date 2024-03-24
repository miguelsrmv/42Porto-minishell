/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:56 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/24 07:43:13 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retirei a parte em secção porque por definição, se entra aqui, ja é "echo"
int	echo(char **args)
{
	bool	print_newline;
	int		i;

	i = 0;
	print_newline = true;
	while (args[i])
		i++;
/* 	if (ft_strncmp(args[i], "echo", ft_strlen(args[i])) != 0)
		return (EXIT_FAILURE);
	i++;*/
	if (i == 1)
	{
		printf("\n");
		g_status_flag = 0;
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (args[i] && check_echo_arg(args[i]) == 2)
	{
		print_newline = false;
		i++;
	}
	if (print_echo(&args[--i], print_newline) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_echo_arg(char *args)
{
	int		i;
	int		n;

	i = 0;
	n = -1;
	if (check_hifen(args, &n, i) == -1)
		return (-1);
	if (n == 0)
		return (2);
	else
		return (1);
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

// Já não precisa desta parte após as trocadas de "" para NULL, acho eu
int	print_echo(char **args, bool print_newline)
{
	int	i;

	i = 1;
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
/* 	{
		if (ft_strcmp(args[i], "") == 0)
			;
		else if (!printf("%s", args[i]))
			return (EXIT_FAILURE);
		else if (ft_strlen(args[i]) != 0 && args[i + 1] != NULL)
			if (!printf(" "))
				return (EXIT_FAILURE);
		i++;
	} */
	if (print_newline)
		if (!printf("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
