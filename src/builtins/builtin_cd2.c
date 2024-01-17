/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:54:07 by bmota-si          #+#    #+#             */
/*   Updated: 2024/01/11 12:11:02 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cd(char *str, t_env *envv)
{
	int		i;
	char	*cwd;

	i = 0;
	cwd = NULL;
	if (str[i] == '-')
	{
		chdir(envv->oldpwd);
		cwd = ft_strdup(envv->oldpwd);
		ft_update_env_var(envv, "OLDPWD", envv->pwd);
		ft_update_env_var(envv, "PWD", cwd);
		ft_printf("%s\n", cwd);
		free(cwd);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

int	ft_exit_cd(char **cwd, int exit_status)
{
	ft_free_str(cwd);
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		g_status_flag = 1;
		perror("Error");
		return (EXIT_FAILURE);
	}
}
