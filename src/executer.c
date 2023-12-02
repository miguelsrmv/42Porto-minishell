/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/01 12:47:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_command_table *current, char **envp, t_memptr memptr)
{
	int	(*function_pointer)(char **);
	int	exit_value;

	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else if (current->command_type == BUILTIN)
	{
		function_pointer = (int (*)(char **))current->builtin_pointer;
		exit_value = function_pointer(current->cmd);
		clean_memory(memptr);
		(void)exit_value;
	}
}
