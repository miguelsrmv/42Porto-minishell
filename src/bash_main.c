/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:54:29 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/07 10:54:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bash_main(char **envp_cpy, t_memptr memptr)
{
	extern enum e_SignalType	g_signal_flag;
	int							pid;
	int							signal_pipe[2];
	int							envv_pipe[2];

	while (TRUE)
	{
		if (g_signal_flag == SIGINT_SIGNAL)
			g_signal_flag = NO_SIGNAL;
		else if (g_signal_flag == EOF_SIGNAL)
			exit(128);
		set_environment_vars(envp_cpy, memptr);
		pipe(signal_pipe);
		pipe(envv_pipe);
		pid = fork();
		if (pid < 0)
			exit_error(FORK_ERROR, memptr);
		else if (pid > 0)
			bash_parent(signal_pipe, pid);
		else
			bash_child(envp_cpy, memptr, signal_pipe, envv_pipe);
		read_envv(envv_pipe, envp_cpy);
		clean_memory(memptr);
	}
}

void	bash_parent(int *signal_pipe, int pid)
{
	extern enum e_SignalType	g_signal_flag;

	set_parent_signal();
	close (signal_pipe[1]);
	read (signal_pipe[0], &g_signal_flag, sizeof(enum e_SignalType));
	close(signal_pipe[1]);
	wait4(pid, NULL, 0, NULL);
}

void	bash_child(char **envp, t_memptr memptr, int *signal_pipe,
			int *envv_pipe)
{
	set_child_signal();
	*(memptr.lexer_list) = read_readline(memptr, signal_pipe);
	*(memptr.command_table) = parse_list(*(memptr.lexer_list), memptr);
	expand_command_table(memptr.command_table, memptr);
	prepare_processes(memptr.command_table, envp, memptr, envv_pipe);
}

void	read_envv(int *envv_pipe, char **envp_cpy)
{
	int		tab_len;
	int		i;
	int		str_len;

	close(envv_pipe[1]);
	ft_free_tabs((void **)envp_cpy);
	read(envv_pipe[0], &tab_len, sizeof(int));
	envp_cpy = (char **)malloc((tab_len + 1) * sizeof(char *));
	i = 0;
	while (i < tab_len)
	{
		read(envv_pipe[0], &str_len, sizeof(int));
		envp_cpy[i] = (char *)malloc(str_len + 1);
		read(envv_pipe[0], envp_cpy[i], str_len);
		envp_cpy[i][str_len] = '\0';
		i++;
	}
	envp_cpy[i] = NULL;
	close(envv_pipe[0]);
}
