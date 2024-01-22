/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/11 12:13:08 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(t_env *envv)
{
	char	*path;

	if (envv->env_var == NULL)
		return (NULL);
	path = get_env_var_value(envv, "HOME");
	if (ft_strlen(path) == 0)
	{
		ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
		ft_free_str(&path);
	}
	return (path);
}

void	ft_update_env_var(t_env *envv, char *var, char *value)
{
	int	i;

	i = 0;
	if (ft_strcmp(var, "OLDPWD") == 0)
	{
		ft_free_str(&envv->oldpwd);
		envv->oldpwd = ft_strdup(envv->pwd);
	}
	if (ft_strcmp(var, "PWD") == 0)
	{
		ft_free_str(&envv->pwd);
		envv->pwd = ft_strdup(value);
	}
	while (envv->env_var && envv->env_var[i])
	{
		if (ft_strcmp(envv->env_var[i], var) == 0
			|| ft_strcmp(envv->env_var[i], var) == 61)
		{
			ft_free_str(&envv->env_var[i]);
			envv->env_var[i] = ft_strstrjoin(ft_strdup(var), value, "=");
			return ;
		}
		i++;
	}
}

int	ft_cd_home(t_env *envv)
{
	char	*home_path;
	char	*cwd;

	cwd = NULL;
	home_path = find_home(envv);
	if (home_path == NULL)
		return (EXIT_FAILURE);
	if (chdir(home_path) != 0)
	{
		ft_free_str(&home_path);
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	}
	ft_update_env_var(envv, "OLDPWD", envv->pwd);
	cwd = getcwd(cwd, 0);
	ft_update_env_var(envv, "PWD", cwd);
	ft_free_str(&home_path);
	if (envv->pwd == NULL || envv->oldpwd == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}

int	cd(char **argv)
{
	t_env	*envv;

	envv = get_envv();
	if (argv == NULL || envv == NULL || argv[2] != NULL)
	{
		g_status_flag = 1;
		return (EXIT_FAILURE);
	}
	if (!ft_strcmp(argv[1], "~"))
		return (ft_cd_home(envv));
	else
		return (ft_cd2(argv, envv));
}

int	ft_cd2(char **argv, t_env *envv)
{
	char	*cwd;
	DIR		*directory;

	cwd = NULL;
	if (ft_check_cd(argv[1], envv) == EXIT_SUCCESS)
		return (ft_exit_cd(&cwd, EXIT_SUCCESS));
	directory = opendir(argv[1]);
	if (directory == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	else if (closedir(directory) != 0)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	else if (chdir(argv[1]) != 0)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	ft_update_env_var(envv, "OLDPWD", envv->pwd);
	cwd = getcwd(cwd, 0);
	ft_update_env_var(envv, "PWD", cwd);
	if (envv->pwd == NULL || envv->oldpwd == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}
