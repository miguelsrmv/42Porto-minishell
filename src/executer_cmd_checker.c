/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/25 11:05:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *command)
{
	return (0);
}

void	test_comamnds(char **path_list, char *command,
			t_command_table **command_table)
{
	int		i;
	char	*test_command;
	char	rel_abs_path[2];

	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i], command);
		if (access(test_command, F_OK | X_OK) == 0)
		{
			(*command_table)->cmd_target = test_comamnd;
			return ;
		}
		free(test_command);
		i++;
	}
	rel_abs_path[0] = ".";
	rel_abs_path[1] = getcwd(NULL, 0);
	i = 0;
	while (rel_abs_path[i])
	{
		test_command = ft_strjoin(rel_abs_path[i], command);
		if (access(test_command, F_OK | X_OK) == 0)
		{
			(*command_table)->cmd_target = test_comamnd;
			return ;
		}
		free(test_command);
		i++;
	}
	(*command_table)->validity = INVALID_CMD;
}

void	check_commands(t_command_table **command_table)
{
	char	*command;
	char	*current_dir;
	char	**path_list;
	char	*temp;

	if (check_builtin(command_table->cmd[0]))
		return ;
	else if ((*command_table)->cmd[0][0] == '.')
	{
		current_dir = getcwd(NULL, 0);
		command = ft_strjoin(current_dir, (*command_table)->cmd[0] + 1);
		free(current_dir);
	}
	else
	{
		command = ft_strdup((*command_table)->cmd[0]);
		temp = command;
		command = ft_strjoin("/", (*command_table)->cmd_target);
		free(temp);
		path_list = ft_split(getenv("PATH"), ':');
	}
	test_commands(path_list, command, command_table);
	free(command);
	ft_free_tabs((void **)path_list);
}
