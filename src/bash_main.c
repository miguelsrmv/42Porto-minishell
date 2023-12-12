/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:54:29 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/12 18:04:47 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*set_environment_vars(char **envp, t_memptr memptr)
{
	t_env						*envv;

	envv = init_envv(envp);
	if (envv == NULL)
		exit_error(ENV_ERROR, memptr);
	//set_envp(envp);
	set_envv(envv);
	return (envv);
}

void	bash_run(char **envp, t_memptr *memptr)
{
	*(memptr->lexer_list) = read_readline(*memptr);
	if (!(memptr->lexer_list))
		return ;
	*(memptr->command_table) = parse_list(*(memptr->lexer_list), *memptr);
	expand_command_table(memptr->command_table, *memptr);
	prepare_processes(memptr->command_table, envp, memptr);
}

void	update_envp(char ***envp, t_memptr *memptr, t_env *env_vars)
{
	ft_free_tabs((void **)*envp);
	*envp = ft_tabdup(env_vars->env_var);
	if (!*envp)
		exit_error(MALLOC_ERROR, *memptr);
	memptr->envp = *envp;
	free_envv(env_vars);
}

void	bash_main(char **envp, t_memptr *memptr)
{
	extern enum e_SignalType	g_signal_flag;
	t_env						*env_vars;

	while (TRUE)
	{
		set_signal();
		if (g_signal_flag != SIGINT_SIGNAL)
			env_vars = set_environment_vars(envp, *memptr);
		else if (g_signal_flag == SIGINT_SIGNAL)
			g_signal_flag = NO_SIGNAL;
		if (g_signal_flag == SIGINT_SIGNAL)
			g_signal_flag = NO_SIGNAL;
		bash_run(envp, memptr);
		update_envp(&envp, memptr, env_vars);
	}
}
