/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:52:31 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 18:24:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_newline_flag(char *flag)
{
	size_t	i;

	if (flag && flag[0] == '-')
	{
		i = 1;
		while (flag[i] == 'n')
			i++;
		if (i == ft_strlen(flag) && i > 1)
			return (false);
	}
	return (true);
}

int	echo(char **args)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (args[i] && !check_newline_flag(args[i]))
	{
		if (i == 1)
			newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
