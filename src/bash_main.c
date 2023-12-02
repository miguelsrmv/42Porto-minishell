/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:54:29 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/02 23:47:01 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bash_main(char **envp, t_memptr memptr)
{
	extern enum e_SignalType	g_signal_flag;
	int							pid;
	int							main_pipe[2];

	while (TRUE)
	{
		if (g_signal_flag == SIGINT_SIGNAL)
			g_signal_flag = NO_SIGNAL;
		else if (g_signal_flag == EOF_SIGNAL)
			exit(128);
		pipe(main_pipe);
		pid = fork();
		if (pid < 0)
			exit_error(FORK_ERROR, memptr);
		else if (pid > 0)
			bash_parent(main_pipe, pid);
		else
			bash_child(envp, memptr, main_pipe);
		clean_memory(memptr);
	}
}

void	bash_parent(int *main_pipe, int pid)
{
	extern enum e_SignalType	g_signal_flag;

	set_parent_signal();
	close (main_pipe[1]);
	read (main_pipe[0], &g_signal_flag, sizeof(enum e_SignalType));
	close(main_pipe[1]);
	wait4(pid, NULL, 0, NULL);
}

void	bash_child(char **envp, t_memptr memptr, int *main_pipe)
{
	set_child_signal();
	*(memptr.lexer_list) = read_readline(memptr, main_pipe);
	*(memptr.command_table) = parse_list(*(memptr.lexer_list), memptr);
	expand_command_table(memptr.command_table, memptr);
	prepare_processes(memptr.command_table, envp, memptr);
}
