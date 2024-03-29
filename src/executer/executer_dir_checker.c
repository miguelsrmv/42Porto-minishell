/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_dir_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:12:06 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 17:18:42 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_directory_subfunc(t_command_table *current, char *test_command,
			t_memptr memptr)
{
	struct stat	st;
	char		*stripped_command;

	free(current->cmd_target);
	current->cmd_target = ft_strdup(test_command);
	if (!current->cmd_target)
		exit_error(MALLOC_ERROR, memptr, NULL);
	if (stat(test_command, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			current->command_type = DIRECTORY;
			return ;
		}
	}
	stripped_command = ft_substr(test_command, 0, ft_strlen(test_command) - 1);
	if (!stripped_command)
		exit_error(MALLOC_ERROR, memptr, NULL);
	if (access(stripped_command, F_OK) == 0)
		current->command_type = NOT_A_DIRECTORY;
	else
		current->command_type = NULL_DIRECTORY;
	free(stripped_command);
}
