/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 17:34:49 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_command_table *current, char **envp)
{
	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else
	{
		ft_fprintf(STDERR_FILENO, "BUILTIN ALERT\n"); // Correr function pointer aqui
		return ;                                      // Exit value ?  
	}
}
