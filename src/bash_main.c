/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:54:29 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/08 18:55:44 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bash_main(char **envp_cpy, t_memptr memptr)
{
	extern enum e_SignalType	g_signal_flag;

	set_signal();
	while (TRUE)
	{
		if (g_signal_flag == NO_SIGNAL)
			set_environment_vars(envp_cpy, memptr);
		else if (g_signal_flag == SIGINT_SIGNAL)
			g_signal_flag = NO_SIGNAL;
		bash_run(envp_cpy, memptr);
	}
}

void	set_environment_vars(char **envp_cpy, t_memptr memptr)
{
	t_env						*envv;

	envv = init_envv(envp_cpy);
	if (envv == NULL)
		exit_error(ENV_ERROR, memptr);
	set_envp(envp_cpy);
	set_envv(envv);
}

void	bash_run(char **envp, t_memptr memptr)
{
	*(memptr.lexer_list) = read_readline(memptr);
	if (!(*memptr.lexer_list))
		return ;
	*(memptr.command_table) = parse_list(*(memptr.lexer_list), memptr);
	expand_command_table(memptr.command_table, memptr);
	prepare_processes(memptr.command_table, envp, memptr);
}
