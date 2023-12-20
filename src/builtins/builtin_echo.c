/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:56 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/19 18:48:05 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	bool	print_newline;
	int		i;

	i = 0;
	print_newline = true;
	if (ft_strncmp(args[i], "echo", ft_strlen(args[i])) != 0)
		return (EXIT_FAILURE);
	i++;
	if (check_echo_arg(args[i]) == 2)
	{
		print_newline = false;
		i++;
	}
	if (print_echo(args, print_newline, i) == EXIT_FAILURE)
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

char	*get_echo_var(char *str)
{
	t_env		*envv;
	char		*str2;
	int			i;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (NULL);
	i = 0;
	while (envv->env_var[i] != NULL)
	{
		if (contains_str(envv->env_var[i], str) == EXIT_SUCCESS)
		{
			str2 = ft_strdup(envv->env_var[i]);
			free(str);
			return (ft_strchr2(str2, '='));
		}
		else
			i++;
	}
	return (NULL);
}

int	contains_str(const char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
	{
		if (str1[i] == str2[i])
		{
			if ((str1[i + 1] == '=') && str2[i + 1] == '\0')
				return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
