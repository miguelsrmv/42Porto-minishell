/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/30 11:43:19 by mde-sa--         ###   ########.fr       */
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

void	absolute_check_executables(t_command_table *current)
{
	char	*test_command;

	test_command = ft_strdup(current->cmd[0]);
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

void	relative_check_executables(t_command_table *current, char **path_list)
{
	int		i;
	char	*test_command;

	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i++], current->cmd[0]);
		if (access(test_command, F_OK) == 0)
		{
			current->cmd_target = test_command;
			if (access(test_command, X_OK) != 0
				&& (current->cmd[0][0] == '.') && (current->cmd[0][1] == '/'))
				current->command_type = PERMISSION;
			else if (opendir(test_command) != NULL
				&& (((current->cmd[0][0] == '.') && (current->cmd[0][1] == '/'))
				|| (current->cmd[0][0] == '/')))
				current->command_type = DIRECTORY;
			else if (opendir(test_command) == NULL
				&& (access(test_command, X_OK) == 0))
				current->command_type = EXECUTABLE;
			return ;
		}
		free(test_command);
	}
}

void	check_executables(t_command_table *current, char **path_list)
{
	if (!path_list || !ft_strlen(*current->cmd))
		return ;
	if (current->cmd[0][0] == '/')
		absolute_check_executables(current);
	else
		relative_check_executables(current, path_list);
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
			exit_error(MALLOC_ERROR, memptr);
		ft_free_tabs((void **)temp);
	}
}

// Temos que tratar desse check_commands2. Depois explicas-me o que é.
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
	/* 		if (current->command_type == NO_NULL_COMMANDTYPE)
				return (check_commands2(current)); */
			if (current->command_type != BUILTIN)
				check_executables(current, path_list);
			if (current->command_type == NULL_COMMANDTYPE)
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
