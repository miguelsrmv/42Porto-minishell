/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:54:29 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 10:50:26 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bash_run(char **envp, t_memptr *memptr)
{
	*(memptr->lexer_list) = read_readline(*memptr);
	if (!*(memptr->lexer_list))
		return ;
	*(memptr->command_table) = parse_list(*(memptr->lexer_list), *memptr);
	if (!(*(memptr->command_table)))
		return ;
	if (g_status_flag == 8)
	{
		g_status_flag = 130;
		return ;
	}
	expand_command_table(memptr->command_table, *memptr);
	prepare_processes(memptr->command_table, envp, memptr);
}

void	bash_main(t_memptr *memptr)
{
	g_status_flag = 0;
	update_shell_level(&memptr->envp, memptr);
	memptr->path_list = ft_split(getenv("PATH"), ':');
	if (!(memptr->path_list))
		exit_error(MALLOC_ERROR, *memptr, NULL);
	while (g_status_flag != EOF_SIGNAL)
	{
		set_signal();
		bash_run(memptr->envp, memptr);
		clean_memory(memptr);
		update_path(memptr);
	}
}
