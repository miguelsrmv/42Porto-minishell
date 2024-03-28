/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_process_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:26:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/28 18:37:22 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_check(t_command_table **command_table,
			char **envp, t_memptr *memptr)
{
	t_command_table	*current;
	bool			run_flag;
	int				command_no;

	(void)envp;
	current = *command_table;
	memptr->path_list = get_path(envp, memptr);
	command_no = 1;
	while (current)
	{
		current->command_no = command_no++;
		run_flag = TRUE;
		run_flag = input_check(&current, memptr);
		if (run_flag)
			run_flag = output_check(&current, memptr);
		if (run_flag)
			run_flag = command_check(&current,
					memptr->path_list, memptr);
		current->current_g_status = g_status_flag;
		current->valid_command = run_flag;
		current = current->next;
	}
}

char	**get_path(char **envp, t_memptr *memptr)
{
	char	**path;

	path = NULL;
	if (check_path(envp) == EXIT_SUCCESS)
		path = get_path_list(memptr);
	return (path);
}

int	check_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH:", 4) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}
