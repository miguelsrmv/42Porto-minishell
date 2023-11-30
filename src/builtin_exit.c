/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/30 15:34:56 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_exit_arg(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_issign(args[i][j]))
				j++;
			if (!ft_isdigit(args[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	exit_inbuilt(char **args)
{
	long	exit_code;
	int		i;

	i = 0;
	if (ft_strncmp(args[i], "exit", ft_strlen(args[i])) != 0)
		return (EXIT_FAILURE);
	i++;
	if (args[i])
		exit_code = ft_atol(args[i]);
	else
		exit_code = 0;
	/* if (!is_valid_exit_arg(args + i)  || ft_strlen(args[i]) > 19)
	{
		ft_fprintf(2, "exit: not a valid argument\n");
		exit_code = 255;
	} */
	if (!is_valid_exit_arg(args + i))
	{
		ft_fprintf(2, "exit: not a valid argument\n");
		exit_code = 255;
	}
	else if (args[i] && args[++i])
	{
		ft_fprintf(2, "exit: too many arguments\n");
		ft_fprintf(2, "exit\n");
		return (EXIT_FAILURE);
	}
	ft_fprintf(2, "exit\n");
	return (exit_code);
}