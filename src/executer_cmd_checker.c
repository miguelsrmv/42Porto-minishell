/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 18:54:41 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtin(t_command_table *current)
{
	if (!ft_strcmp(current->cmd[0], "echo"))
		current->builtin_pointer = (void *)echo;
	else if (!ft_strcmp(current->cmd[0], "cd"))
		current->builtin_pointer = (void *)cd;
	else if (!ft_strcmp(current->cmd[0], "pwd"))
		current->builtin_pointer = (void *)pwd;
	else if (!ft_strcmp(current->cmd[0], "export"))
		current->builtin_pointer = (void *)export;
	else if (!ft_strcmp(current->cmd[0], "unset"))
		current->builtin_pointer = (void *)unset;
	else if (!ft_strcmp(current->cmd[0], "env"))
		current->builtin_pointer = (void *)env;
	else if (!ft_strcmp(current->cmd[0], "exit"))
		current->builtin_pointer = (void *)exit;
	if (current->builtin_pointer)
		current->command_type = BUILTIN;
}

void	check_executables(t_command_table *current, char **path_list)
{
	int				i;
	char			*test_command;

	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i], current->cmd[0]);
		if (access(test_command, F_OK | X_OK) == 0)					// Acrescentar SE NAO FOR UMA PASTA!!
		{
			current->cmd_target = test_command;
			current->command_type = EXECUTABLE;
			return ;
		}
		free(test_command);
		i++;
	}
}

void	check_commands(t_command_table **command_table, char **path_list,
			t_memptr memptr)
{	
	t_command_table	*current;

	current = (*command_table);
	while (current)
	{
		check_builtin(current);
		if (current->command_type != BUILTIN)
			check_executables(current, path_list);
		if (current->command_type == NULL_COMMANDTYPE)
			exit_error(COMMAND_ERROR, memptr, current->cmd[0]);
		current = current->next;
	}
}
