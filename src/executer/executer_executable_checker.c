/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_executable_checker.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:39:27 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/30 14:39:48 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	absolute_check_executables(t_command_table *current, t_memptr memptr)
{
	char	*test_command;

	test_command = ft_strdup(current->cmd[0]);
	if (!test_command)
		exit_error(MALLOC_ERROR, memptr);
	if (access(test_command, F_OK) == 0)
	{
		current->cmd_target = test_command;
		if (access(test_command, X_OK) != 0)
			current->command_type = PERMISSION;
		else if (opendir(test_command) != NULL)
			current->command_type = DIRECTORY;
		else if (opendir(test_command) == NULL
			&& (access(test_command, X_OK) == 0))
			current->command_type = EXECUTABLE;
	}
}

void	relative_check_executables(t_command_table *current, char **path_list,
			t_memptr memptr)
{
	int		i;
	char	*test_command;

	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i++], current->cmd[0]);
		if (!test_command)
			exit_error(MALLOC_ERROR, memptr);
		if (access(test_command, F_OK) == 0)
		{
			current->cmd_target = test_command;
			if (access(test_command, X_OK) != 0
				&& (current->cmd[0][0] == '.') && (current->cmd[0][1] == '/'))
				current->command_type = PERMISSION;
			else if (opendir(test_command) != NULL
				&& ((current->cmd[0][0] == '.') && (current->cmd[0][1] == '/')))
				current->command_type = DIRECTORY;
			else if (opendir(test_command) == NULL
				&& (access(test_command, X_OK) == 0))
				current->command_type = EXECUTABLE;
			return ;
		}
		free(test_command);
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
