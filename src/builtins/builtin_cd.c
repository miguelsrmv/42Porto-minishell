/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 10:01:22 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	attempt_to_change_dir(char *path, t_memptr *memptr)
{
	char	*new_dir;

	if (chdir(path) != 0)
	{
		perror("cd");
		g_status_flag = 2;
		return ;
	}
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		perror("Error");
		g_status_flag = 1;
		return ;
	}
	update_oldpwd_location(new_dir, memptr);
	update_pwd_location(new_dir, memptr);
	free(new_dir);
}

void	zigzag_directories(t_memptr *memptr)
{
	char	*path;

	if (find_env_var(memptr->envp, "OLDPWD") == -1)
	{
		g_status_flag = 1;
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return ;
	}
	path = get_env_value(memptr->envp, "OLDPWD", memptr);
	attempt_to_change_dir(path, memptr);
	path = get_env_value(memptr->envp, "PWD", memptr);
	if (!g_status_flag)
		printf("%s\n", path);
}

void	go_home(t_memptr *memptr)
{
	char	*home;

	home = get_env_value(memptr->envp, "HOME", memptr);
	if (!home)
	{
		g_status_flag = 1;
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return ;
	}
	attempt_to_change_dir(home, memptr);
}

int	cd(char **argv, char **envp, t_command_table *current, t_memptr *memptr)
{
	int	arg_number;

	(void)envp;
	(void)current;
	if (builtin_argument_checker(argv) == EXIT_FAILURE)
		return (g_status_flag);
	arg_number = ft_tablen((void **)argv) - 1;
	if (arg_number > 1)
	{
		g_status_flag = 1;
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	}
	else if (arg_number == 0)
		go_home(memptr);
	else if (!ft_strcmp("-", argv[1]))
		zigzag_directories(memptr);
	else
		attempt_to_change_dir(argv[1], memptr);
	return (g_status_flag);
}
