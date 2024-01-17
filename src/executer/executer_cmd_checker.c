/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/17 12:03:02 by bmota-si         ###   ########.fr       */
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
	current->cmd = ft_str_arr_dup(removeEmptyStrings(current->cmd));
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

void	check_executables(t_command_table *current, char **path_list,
			t_memptr memptr)
{
	int				i;
	char			*test_command;

	if (!path_list)
		return ;
	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i], current->cmd[0]);
		if (access(test_command, F_OK | X_OK) == 0)
		{
			if (opendir(test_command) != NULL)
				exit_error(DIRECTORY_ERROR, memptr, test_command);
			current->cmd_target = test_command;
			current->command_type = EXECUTABLE;
			return ;
		}
		free(test_command);
		i++;
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

int	check_commands(t_command_table **command_table, char **path_list,
			t_memptr memptr)
{
	t_command_table	*current;

	current = (*command_table);
	while (current)
	{
		check_builtin(current);
		if (current->command_type == NO_NULL_COMMANDTYPE)
			return (check_commands2(current));
		if (current->command_type != BUILTIN)
			check_executables(current, path_list, memptr);
		if (current->command_type == NULL_COMMANDTYPE)
		{
			g_status_flag = 127;
			ft_fprintf(STDERR_FILENO, "%s: %s", current->cmd[0], COMMAND_ERROR);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
