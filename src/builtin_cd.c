/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/07 18:33:35 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home(t_env *envv)
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

static void	ft_update_env_var(t_env *envv, char *var, char *value)
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

static int	ft_exit_cd(char **cwd, int exit_status)
{
	ft_free_str(cwd);
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
}

static int	ft_cd_home(t_env *envv)
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
	//envp = ft_tabdup(envv->envp);
	if (envv->pwd == NULL || envv->oldpwd == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}

/* int		ft_check_cd(char *str, t_env *envv)
{
	int i = 0;

	if(str[i] == '-')
	{
		chdir(envv->oldpwd);
		//cwd = envv->oldpwd;
		ft_update_env_var(envv, "OLDPWD", envv->pwd);
		ft_update_env_var(envv, "PWD", envv->oldpwd);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
} */

int	cd(char **argv)
{
	char	*cwd;
	DIR		*directory;
	t_env	*envv;

	envv = get_envv();
	if (argv == NULL || envv == NULL)
		return (EXIT_FAILURE);
	if (argv[1] == NULL)
		return (ft_cd_home(envv));
	cwd = NULL;
	/* if (ft_check_cd(argv[1], envv))
		return (ft_exit_cd(&cwd, EXIT_SUCCESS));
	else
		return (ft_exit_cd(&cwd, EXIT_FAILURE)); */
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
	//envp = ft_tabdup(envv->envp);
	if (envv->pwd == NULL || envv->oldpwd == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}
