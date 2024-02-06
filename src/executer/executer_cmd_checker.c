/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 20:16:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtin(t_command_table *current)
{
	if (!(current->cmd[0]))
		return ;
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
		current->builtin_pointer = (void *)ft_exit;
	if (current->builtin_pointer)
		current->command_type = BUILTIN;
}

void	remove_null_strings(t_command_table *current, t_memptr memptr)
{
	int		i;
	char	**temp;

	i = 0;
	while (current->cmd[i] && !ft_strlen(current->cmd[i]))
		i++;
	if (i == 0)
		return ;
	else
	{
		temp = current->cmd;
		current->cmd = ft_tabdup(&current->cmd[i]);
		if (!current->cmd)
			exit_error(MALLOC_ERROR, memptr, NULL);
		ft_free_tabs((void **)temp);
	}
}

// Alterei para também dar erro em caso de No Null Command Type
int	check_commands(t_command_table **command_table, char **path_list,
			t_memptr memptr)
{
	t_command_table	*current;

	current = (*command_table);
	while (current)
	{
		remove_null_strings(current, memptr);
		if (current->cmd[0])
		{
			check_builtin(current);
			if (current->command_type != BUILTIN)
				check_executables(current, path_list, memptr);
			if (current->command_type == NULL_COMMANDTYPE
				|| current->command_type == NO_NULL_COMMANDTYPE)
				non_exit_error(COMMAND_ERROR, memptr, *current->cmd);
			else if (current->command_type == DIRECTORY)
				non_exit_error(DIRECTORY_ERROR, memptr, current->cmd_target);
			else if (current->command_type == PERMISSION)
				non_exit_error(PERMISSION_ERROR, memptr, current->cmd_target);
		}
		current = current->next;
	}
	return (1);
}
