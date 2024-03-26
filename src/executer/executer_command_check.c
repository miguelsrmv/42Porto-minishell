/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:45:33 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/26 00:36:58 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	command_check(t_command_table **command,
			char **path, t_memptr *memptr)
{
	remove_null_strings((*command), *memptr);
	(*command)->cmd = final_nullstrings(*command, *memptr);
	if ((*command)->cmd[0])
	{
		check_builtin((*command));
		if ((*command)->command_type != BUILTIN)
			check_executables((*command), path, *memptr);
		if ((*command)->command_type == NULL_COMMANDTYPE
			|| (*command)->command_type == NO_NULL_COMMANDTYPE)
			non_exit_error(COMMAND_ERROR, *memptr, *(*command)->cmd);
		else if ((*command)->command_type == DIRECTORY)
			non_exit_error(DIRECTORY_ERROR, *memptr, *(*command)->cmd);
		else if ((*command)->command_type == NOT_A_DIRECTORY)
			non_exit_error(NOT_A_DIR_ERROR, *memptr, *(*command)->cmd);
		else if ((*command)->command_type == NULL_DIRECTORY)
			non_exit_error(DIR_OPEN_ERROR, *memptr, *(*command)->cmd);
		else if ((*command)->command_type == PERMISSION)
			non_exit_error(PERMISSION_ERROR, *memptr, (*command)->cmd_target);
	}
	if ((*command)->command_type == BUILTIN
		|| ((*command)->command_type) == EXECUTABLE)
		return (TRUE);
	if (!(*command)->cmd[0])
		g_status_flag = 0;
	return (FALSE);
}

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
