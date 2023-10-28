/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/28 14:39:46 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *command)
{
	if (ft_strcmp(command, "echo12345") == 0)
		return (1);
	return (0);
}

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

void	check_commands(t_command_table **command_table, char **path_list)
{
	char	*test_command;
	int		i;

	if (check_builtin((*command_table)->cmd[0]))
	{
		return ;
	}
	i = 0;
	while (path_list[i])
	{
		test_command = ft_strjoin(path_list[i], (*command_table)->cmd[0]);
		if (access(test_command, F_OK | X_OK) == 0)
		{
			(*command_table)->cmd_target = test_command;
			(*command_table)->command_type = EXECUTABLE;
			return ;
		}
		free(test_command);
		i++;
	}
	ft_printf("minishell: %s: command not found\n", (*command_table)->cmd[0]);
	return ; // Error
}
