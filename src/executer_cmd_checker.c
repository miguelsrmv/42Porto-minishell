/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 10:30:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_list(void)
{
	char	**path_list;
	int		i;
	char	**result;
	char	*temp;

	path_list = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path_list[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 3));
	result[0] = ft_strdup("./");
	temp = getcwd(NULL, 0);
	result[1] = ft_strjoin(temp, "/");
	free(temp);
	i = 0;
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		result[i + 2] = ft_strdup(temp);
		free(temp);
		i++;
	}
	result[i + 2] = NULL;
	ft_free_tabs((void **)path_list);
	return (result);
}

void	check_builtin(t_command_table *current)
{
	if (!ft_strcmp(current->cmd[0], "echo"))
		current->builtin_pointer = (void *)builtin_placeholder;
	else if (!ft_strcmp(current->cmd[0], "cd"))
		current->builtin_pointer = (void *)builtin_placeholder;
	else if (!ft_strcmp(current->cmd[0], "pwd"))
		current->builtin_pointer = (void *)builtin_placeholder;
	else if (!ft_strcmp(current->cmd[0], "export"))
		current->builtin_pointer = (void *)builtin_placeholder;
	else if (!ft_strcmp(current->cmd[0], "unset"))
		current->builtin_pointer = (void *)builtin_placeholder;
	else if (!ft_strcmp(current->cmd[0], "env"))
		current->builtin_pointer = (void *)builtin_placeholder;
	else if (!ft_strcmp(current->cmd[0], "exit"))
		current->builtin_pointer = (void *)builtin_placeholder;
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
		if (access(test_command, F_OK | X_OK) == 0)
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
	t_command_table *current;

	current = (*command_table);
	while (current)
	{
		check_builtin(current);
		if (current->command_type != BUILTIN)
			check_executables(current, path_list);
		if (current->command_type == NULL_COMMANDTYPE)
		{
			ft_fprintf(STDERR_FILENO, current->cmd[0]);
			exit_error(COMMAND_ERROR, memptr);
		}
		current = current->next;
	}
}
