/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:54:29 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/02 20:09:17 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bash_main(t_token *lexer_list, t_command_table *command_table,
			t_memptr memptr, char **envp)
{
	extern int	signal_flag;
	int			pid;
	int			main_pipe[2];

	while (TRUE)
	{
		if (signal_flag == 1)
			signal_flag = 0;
		else if (signal_flag == 2)
			exit(128);
		pipe(main_pipe);
		pid = fork();
		if (pid < 0)
			exit_error(FORK_ERROR, memptr);
		else if (pid > 0)
			bash_parent(main_pipe);
		else
			bash_child(lexer_list, command_table, memptr, envp, main_pipe);
	}
}

void	bash_parent(int *main_pipe)
{
	extern int	signal_flag;

	set_parent_signal();
	close (main_pipe[1]);
	read (main_pipe[0], &signal_flag, sizeof(int));
	close(main_pipe[1]);
	wait(NULL);
}

void	bash_child(t_token *lexer_list, t_command_table *command_table,
			t_memptr memptr, char **envp, int *main_pipe)
{
	extern int	signal_flag;

	set_child_signal();
	lexer_list = read_readline(memptr, main_pipe);
	command_table = parse_list(lexer_list, memptr);
	expand_command_table(&command_table, memptr);
	prepare_processes(&command_table, envp, memptr);
	clean_memory(memptr);
}
