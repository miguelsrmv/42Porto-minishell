/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:56 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/12 16:49:18 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	bool	print_newline;

	print_newline = true;
	if (ft_strncmp(*args, "echo", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	if (*args && ft_strncmp(*args, "-n", ft_strlen("-n") + 1) == 0)
	{
		print_newline = false;
		args++;
	}
	while (*args)
	{
		if (!ft_printf("%s", *args))
			return (EXIT_FAILURE);
		if (ft_strlen(*args) != 0 && *(args + 1) != NULL)
			if (!ft_printf(" "))
				return (EXIT_FAILURE);
		args++;
	}
	if (print_newline)
		if (!ft_printf("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*ft_strchr2(const char *s, int c)
{
	while (*s && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
	{
		s++;
		return ((char *)s);
	}
	return (0);
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
