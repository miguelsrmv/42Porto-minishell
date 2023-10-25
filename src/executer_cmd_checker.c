/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:48 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/25 14:06:26 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *command)
{
	return (0);
}

char	**path_list(void)
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
	i = 0;
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		result[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	result[i] = ft_strdup("./");
	temp = getcwd(NULL, 0);
	result[i + 1] = ft_strjoin(temp, "/");
	free(temp);
	result[i + 2] = NULL;
	ft_free_tabs((void **)path_list);
	return (result);
}

void	check_commands(t_command_table **command_table)
{
	char **path_list;
	char *test_command;
	int	i;

	if (check_builtin((*command_table)->command))
	{
		return ;
	}
	path_list = path_list();
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
	(*command_table)->validity = INVALID_CMD;
}
