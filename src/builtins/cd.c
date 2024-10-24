/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/24 11:58:04 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_locations(char *old_dir, char *new_dir, t_memptr *memptr)
{
	int	oldpwd_position;
	int	pwd_position;

	oldpwd_position = find_env_var(memptr->envp, "OLDPWD");
	pwd_position = find_env_var(memptr->envp, "PWD");
	if (pwd_position == -1 || !ft_strcmp(memptr->envp[pwd_position], "PWD="))
		memptr->unset_pwd_flag++;
	else
		memptr->unset_pwd_flag = 0;
	if (oldpwd_position >= 0)
	{ // NOTE: Changed this for bash linux vs WSL
		if (memptr->unset_pwd_flag != 1 || pwd_position >= 0)
			set_env_value(memptr->envp, "OLDPWD", old_dir, memptr);
		else
			set_env_value(memptr->envp, "OLDPWD", NULL, memptr);
	}
	if (pwd_position >= 0)
		set_env_value(memptr->envp, "PWD", new_dir, memptr);
	free(memptr->my_pwd);
	free(memptr->my_oldpwd);
	memptr->my_pwd = new_dir;
	memptr->my_oldpwd = old_dir;
	g_status_flag = EXIT_SUCCESS;
	return (g_status_flag);
}

int	attempt_to_change_dir(char *path, t_memptr *memptr)
{
	char	*old_dir;
	char	*new_dir;

	if (find_env_var(memptr->envp, "PWD") != -1)
		old_dir = ft_strdup(get_env_value(memptr->envp, "PWD", memptr));
	else
		old_dir = ft_strdup(memptr->my_pwd);
	if (!old_dir)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_dir);
		g_status_flag = 2;
		return (g_status_flag);
	}
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		perror("Error");
		free(old_dir);
		g_status_flag = 1;
		return (g_status_flag);
	}
	return (update_locations(old_dir, new_dir, memptr));
}

void	go_home(t_memptr *memptr)
{
	char	*home;

	home = get_env_value(memptr->envp, "HOME", memptr);
	if (!home)
		return (error_message("cd: HOME not set\n", EXIT_FAILURE));
	attempt_to_change_dir(home, memptr);
}
/*int	attempt_to_change_dir(char *path, t_memptr *memptr)
{
	char	*new_dir;
	char	*old_dir;

	if (find_env_var(memptr->envp, "PWD") != -1)
		old_dir = ft_strdup(get_env_value(memptr->envp, "PWD", memptr));
	else
		old_dir = ft_strdup(memptr->my_pwd);
	if (!old_dir)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_dir);
		g_status_flag = 2;
		return (g_status_flag);
	}
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		perror("Error");
		free(old_dir);
		g_status_flag = 1;
		return (g_status_flag);
	}
	update_locations(old_dir, new_dir, memptr);
	return (EXIT_SUCCESS);
}*/
/*
void	go_oldpwd(t_memptr *memptr, int oldpwd_position)
{
	if (oldpwd_position == -1)
		return (error_message("cd: OLDPWD not set\n", EXIT_FAILURE));
	else if (!ft_strcmp(memptr->envp[oldpwd_position], "OLDPWD="))
	// HACK ???? Era OLDPWD=
	// else if (ft_strlen(memptr->envp[oldpwd_position]) <= 7)
	{
		if (find_env_var(memptr->envp, "PWD") >= 0 || memptr->my_oldpwd)
		{
			set_env_value(memptr->envp, "OLDPWD", get_env_value(memptr->envp,
					"PWD", memptr), memptr);
			if (memptr->my_oldpwd)
			{
				free(memptr->my_oldpwd);
				memptr->my_oldpwd = NULL;
				return (error_message("cd: OLDPWD not set\n", EXIT_FAILURE));
			}
			return (error_message("\n", EXIT_SUCCESS));
		}
		else
			return (error_message("cd: OLDPWD not set\n", EXIT_FAILURE));
	}
	if (attempt_to_change_dir(get_env_value(memptr->envp, "OLDPWD", memptr),
			memptr) == EXIT_SUCCESS)
		printf("%s\n", memptr->my_pwd);
}
*/

void	go_oldpwd(t_memptr *memptr, int oldpwd_position)
{
	char	*oldpwd_value;

	if (oldpwd_position == -1)
		return (error_message("cd: OLDPWD not set\n", EXIT_FAILURE));
	oldpwd_value = get_env_value(memptr->envp, "OLDPWD", memptr);
	if ((oldpwd_value == NULL || !ft_strlen(oldpwd_value)))
	{
		if (!memptr->my_oldpwd)
			return (error_message("cd: OLDPWD not set\n", EXIT_FAILURE));
		else
		{
			free(memptr->my_oldpwd);
			// memptr->my_oldpwd = NULL;
			// TODO: Remove??? Remove lines down to return (not inclusive ) ?
			memptr->my_oldpwd = ft_strdup(memptr->my_pwd);
			if (!memptr->my_oldpwd)
				exit_error(MALLOC_ERROR, *memptr, NULL);
			set_env_value(memptr->envp, "OLDPWD", get_env_value(memptr->envp,
					"PWD", memptr), memptr);
			return (error_message("\n", EXIT_SUCCESS));
		}
	}
	if (attempt_to_change_dir(oldpwd_value, memptr) == EXIT_SUCCESS)
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
		error_message("cd: too many arguments\n", 1);
	else if (arg_number == 0)
		go_home(memptr);
	else if (!ft_strcmp("-", argv[1]))
		go_oldpwd(memptr, find_env_var(memptr->envp, "OLDPWD"));
	else
		attempt_to_change_dir(argv[1], memptr);
	return (g_status_flag);
}
