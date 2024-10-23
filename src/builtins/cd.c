/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/23 12:36:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_locations(char *old_dir, char *new_dir, t_memptr *memptr)
{
	if (find_env_var(memptr->envp, "PWD") == -1)
		memptr->unset_pwd_flag++;
	else
		memptr->unset_pwd_flag = 0;
	update_oldpwd_location(old_dir, memptr);
	update_pwd_location(new_dir, memptr);
	free(memptr->my_pwd);
	free(memptr->my_oldpwd);
	memptr->my_pwd = new_dir;
	memptr->my_oldpwd = old_dir;
}

void	attempt_to_change_dir(char *path, t_memptr *memptr)
{
	char	*new_dir;
	char	*old_dir;

	old_dir = ft_strdup(memptr->my_pwd);
	if (!old_dir)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_dir), g_status_flag = 2;
		return ;
	}
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		perror("Error");
		free(old_dir);
		g_status_flag = 1;
		return ;
	}
	update_locations(old_dir, new_dir, memptr);
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

void	go_oldpwd(t_memptr *memptr)
{
	int		oldpwd_position;
	char	*target_dir;

	oldpwd_position = find_env_var(memptr->envp, "OLDPWD");
	if (oldpwd_position == -1 || !ft_strcmp(memptr->envp[oldpwd_position],
			"OLDPWD="))
	{
		g_status_flag = 1;
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return ;
	}
	target_dir = get_env_value(memptr->envp, "OLDPWD", memptr);
	attempt_to_change_dir(target_dir, memptr);
	printf("%s\n", memptr->my_pwd);
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
		go_oldpwd(memptr);
	else
		attempt_to_change_dir(argv[1], memptr);
	return (g_status_flag);
}
