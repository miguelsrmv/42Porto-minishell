/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/23 20:59:47 by mde-sa--         ###   ########.fr       */
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
		current->builtin_pointer = (void *)ft_exit;
	if (current->builtin_pointer)
		current->command_type = BUILTIN;
}

char	**remove_empty_strings(char **array)
{
	int		i;
	int		j;
	int		count_empty;
	char	**new_array;

	i = 0;
	count_empty = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], ""))
			count_empty++;
		i++;
	}
	new_array = (char **) malloc((i - count_empty) * sizeof (char *));
	if (new_array == NULL)
	{
		perror("Falha ao alocar memória");
		exit(EXIT_FAILURE);
	}
	j = 0;
	i = 0;
	while (array[i])
	{
		while ((!ft_strcmp(array[i], "")) && array[i])
			i++;
		new_array[j] = ft_strdup(array[i]);
		i++;
		j++;
	}
	new_array[j] = NULL;
	ft_free_str_array(&array);
	return (new_array);
}

void	check_builtin2(t_command_table *current)
{
	int		i;

	i = 0;
	current->cmd = ft_str_arr_dup(remove_empty_strings(current->cmd));
	while (current->cmd[i])
	{
		if (!ft_strcmp(current->cmd[i], "echo"))
			current->builtin_pointer = (void *)echo;
		else if (!ft_strcmp(current->cmd[i], "cd"))
			current->builtin_pointer = (void *)cd;
		else if (!ft_strcmp(current->cmd[i], "pwd"))
			current->builtin_pointer = (void *)pwd;
		else if (!ft_strcmp(current->cmd[i], "export"))
			current->builtin_pointer = (void *)export;
		else if (!ft_strcmp(current->cmd[i], "unset"))
			current->builtin_pointer = (void *)unset;
		else if (!ft_strcmp(current->cmd[i], "env"))
			current->builtin_pointer = (void *)env;
		else if (!ft_strcmp(current->cmd[i], "exit"))
			current->builtin_pointer = (void *)ft_exit;
		if (current->builtin_pointer)
		{
			current->command_type = BUILTIN;
			break ;
		}
		else
			i++;
	}
}

void	check_executables(t_command_table *current, char **path_list)
{
	int				i;
	char			*test_command;

	if (!path_list)
		return ;
	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i++], current->cmd[0]);
		if (access(test_command, F_OK) == 0)
		{
			current->cmd_target = ft_strdup(test_command);
			if (access(test_command, X_OK) != 0)
				current->command_type = PERMISSION;
			else if (opendir(test_command) != NULL)
				current->command_type = DIRECTORY;
			else
				current->command_type = EXECUTABLE;
			free(test_command);
			return ;
		}
		free(test_command);
	}
}

int	check_commands2(t_command_table *current)
{
	if (ft_strcmp(current->cmd[0], "") == 0 && current->cmd[1] == NULL)
	{
		g_status_flag = 0;
		return (0);
	}
	else if (ft_strcmp(current->cmd[0], "")
		== 0 && current->cmd[1] != NULL)
		check_builtin2(current);
	else
	{
		g_status_flag = 126;
		ft_fprintf(STDERR_FILENO, "%s: %s", current->cmd[0], DIRECTORY_ERROR);
		return (0);
	}
	return (1);
}

// Temos que tratar desse check_commands2. Depois explicas-me o que é.
int	check_commands(t_command_table **command_table, char **path_list,
			t_memptr memptr)
{
	t_command_table	*current;

	current = (*command_table);
	while (current)
	{
		check_builtin(current);
/* 		if (current->command_type == NO_NULL_COMMANDTYPE)
			return (check_commands2(current)); */
		if (current->command_type != BUILTIN)
			check_executables(current, path_list);
		if (current->command_type == NULL_COMMANDTYPE)
			non_exit_error(COMMAND_ERROR, memptr, current->cmd_target);
		else if (current->command_type == DIRECTORY)
			non_exit_error(DIRECTORY_ERROR, memptr, current->cmd_target);
		else if (current->command_type == PERMISSION)
			non_exit_error(PERMISSION_ERROR, memptr, current->cmd_target);
		current = current->next;
	}
	return (1);
}
