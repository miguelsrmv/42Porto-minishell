/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:56 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 11:25:05 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	bool	print_newline;
	int		i;

	i = 0;
	print_newline = true;
	while (ft_strcmp(args[i], "") == 0)
		i++;
	if (ft_strncmp(args[i], "echo", ft_strlen(args[i])) != 0)
		return (EXIT_FAILURE);
	i++;
	if (!args[i])
	{
		g_status_flag = 0;
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	while (args[i] && check_echo_arg(args[i]) == 2)
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

char	*get_echo_var(char *str, t_memptr memptr)
{
	t_env		*envv;
	char		*result;
	int			i;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (NULL);
	i = 0;
	result = NULL;
	while (envv->env_var[i] != NULL)
	{
		if (contains_str(envv->env_var[i], str) == EXIT_SUCCESS)
		{
			result = ft_strchr2(envv->env_var[i], '=');
			break ;
		}
		i++;
	}
	if (ft_isdigit(*str) && ft_atoi(str) < memptr.argc)
	{
		result = ft_strdup(memptr.argv[ft_atoi(str)]);
		if (!result)
			exit_error(MALLOC_ERROR, memptr, NULL);
	}
	return (result);
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
