/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_executable_checker.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:39:27 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 17:58:48 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	absolute_check_executables(t_command_table *current, t_memptr memptr)
{
	char	*test_command;

	test_command = ft_strdup(current->cmd[0]);
	if (!test_command)
		exit_error(MALLOC_ERROR, memptr, NULL);
	if (access(test_command, F_OK) == 0)
	{
		current->cmd_target = test_command;
		if (access(test_command, X_OK) != 0)
			current->command_type = PERMISSION;
		else
			absolute_check_executables_subfunc(current, test_command);
	}
	else
	{
		free(test_command);
		current->command_type = NULL_COMMANDTYPE;
	}
}

void	absolute_check_executables_subfunc(t_command_table *current,
			char *test_command)
{
	DIR		*dir;

	dir = opendir(test_command);
	if (dir != NULL)
		current->command_type = DIRECTORY;
	else if (dir == NULL
		&& (access(test_command, X_OK) == 0))
		current->command_type = EXECUTABLE;
	closedir(dir);
}

void	relative_check_executables(t_command_table *current,
			char **path_list, t_memptr memptr)
{
	int		i;
	char	*test_command;

	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i++], current->cmd[0]);
		if (!test_command)
			exit_error(MALLOC_ERROR, memptr, NULL);
		if (access(test_command, F_OK) == 0)
		{
			relative_check_executables_subfunc(current, test_command);
			return ;
		}
		free(test_command);
	}
}

void	relative_check_executables_subfunc(t_command_table *current,
			char *test_command)
{
	DIR	*dir;

	current->cmd_target = test_command;
	if (access(test_command, X_OK) != 0
		&& (current->cmd[0][0] == '.') && (current->cmd[0][1] == '/'))
		current->command_type = PERMISSION;
	else
	{
		dir = opendir(test_command);
		if (dir != NULL
			&& (((current->cmd[0][0] == '.') && (current->cmd[0][1] == '/'))
			|| ft_last_char(current->cmd[0]) == '/'))
			current->command_type = DIRECTORY;
		else if (dir == NULL && (access(test_command, X_OK) == 0))
			current->command_type = EXECUTABLE;
		closedir(dir);
	}
}

void	check_executables(t_command_table *current, char **path_list,
			t_memptr memptr)
{
	if (!path_list || !ft_strlen(*current->cmd))
		return ;
	if (current->cmd[0][0] == '/')
		absolute_check_executables(current, memptr);
	else
		relative_check_executables(current, path_list, memptr);
}
