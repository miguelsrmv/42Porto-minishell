/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:54:07 by bmota-si          #+#    #+#             */
/*   Updated: 2024/03/15 17:20:36 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cd(char *str, t_env *envv)
{
	char	*cwd;

	cwd = NULL;
	if (!ft_strcmp(str, "-"))
	{
		chdir(envv->oldpwd);
		cwd = ft_strdup(envv->oldpwd);
		ft_update_env_var(envv, "OLDPWD", envv->pwd);
		ft_update_env_var(envv, "PWD", cwd);
		printf("%s\n", cwd);
		free(cwd);
		return (EXIT_SUCCESS);
	}
	else if (str[0] == '-' && str[1] != '\0')
	{
		g_status_flag = 2;
		return (EXIT_FAILURE);
	}
	else
	{
		g_status_flag = 1;
		return (EXIT_FAILURE);
	}
}

int	ft_exit_cd(char **cwd, int exit_status)
{
	ft_free_str(cwd);
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (g_status_flag != 2)
	{
		perror("bash: cd: ");
		return (EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd("bash: cd: invalid option.\n", STDERR_FILENO);
		return (g_status_flag);
	}
}
