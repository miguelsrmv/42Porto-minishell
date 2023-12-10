/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/10 11:05:40 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_processes(t_command_table **command_table)
{
	t_command_table	*current;
	int				processes_count;

	current = *command_table;
	processes_count = 1;
	while (current)
	{
		if (current->next)
			processes_count++;
		current = current->next;
	}
	return (processes_count);
}

void	process_commands(t_command_table **command_table, char **envp,
			int *envp_pipe, t_memptr memptr)
{
	int				process_num;
	int				**pipe_fd;
	t_command_table	*current;

	process_num = count_processes(command_table);
	pipe_fd = NULL;
	pipe_fd = create_pipes(pipe_fd, process_num - 1, &memptr);
	current = create_processes(command_table, process_num);
	close_pipes(pipe_fd, current, memptr);
	check_redirections(pipe_fd, &current, memptr);
	execute(current, envp, memptr, envp_pipe);
}

void	execute(t_command_table *current, char **envp, t_memptr memptr,
			int *envp_pipe)
{
	int		(*function_pointer)(char **, char **);
	int		exit_value;
	t_env	*envv;

	set_signal_during_processes_child();
	// Expandir exit status mais recente!!
	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envp);
	else if (current->command_type == BUILTIN)
	{
		function_pointer = (int (*)(char **, char **))current->builtin_pointer;
		exit_value = function_pointer(current->cmd, envp);
		if (!current->next && (!ft_strcmp(current->cmd[0], "export")
				|| !ft_strcmp(current->cmd[0], "cd")
				|| !ft_strcmp(current->cmd[0], "unset")
				|| !ft_strcmp(current->cmd[0], "env")))
		{
			envv = get_envv();
			// ft_free_tabs((void **)envp);
			envp = ft_tabdup(envv->env_var);
			write_envp(envp_pipe, envp, memptr);
			free(envv);
		}
		else
		{
			if (close(envp_pipe[0]) == -1 || (close(envp_pipe[1]) == -1))
				exit_error(CLOSE_ERROR, memptr);
			envp_pipe = NULL;
		}
		exit(exit_value);
	}
	// Falta mandar o exit value para $? para expandir depois!!
}
