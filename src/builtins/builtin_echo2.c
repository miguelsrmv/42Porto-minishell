/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:49:43 by bmota-si          #+#    #+#             */
/*   Updated: 2024/03/23 13:07:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if ((str1[i + 1] == '=' || str1[i + 1] == '\0')
				&& str2[i + 1] == '\0')
				return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
