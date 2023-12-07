/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/07 11:01:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_command_table *current, char **envp, t_memptr memptr,
			int *envv_pipe)
{
	int	(*function_pointer)(char **);
	int	exit_value;

	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else if (current->command_type == BUILTIN)
	{
		function_pointer = (int (*)(char **))current->builtin_pointer;
		exit_value = function_pointer(current->cmd);
		if (!current->next) // e se for um builtin que escreva envvars
			write_envv(envv_pipe, envp);
		exit(exit_value);
		(void)memptr;
		(void)envv_pipe;
	}
}

void	write_envv(int *envv_pipe, char **envp)
{
	int							tab_len;
	int							str_len;

	close(envv_pipe[0]);
	tab_len = 0;
	while (envp[tab_len])
		tab_len++;
	write(envv_pipe[1], &tab_len, sizeof(int));
	tab_len = 0;
	while (envp[tab_len])
	{
		str_len = ft_strlen(envp[tab_len]);
		write(envv_pipe[1], &str_len, sizeof(int));
		write(envv_pipe[1], envp[tab_len], str_len + 1);
		tab_len++;
	}
	close(envv_pipe[1]);
}
