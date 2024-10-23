/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:54:29 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/23 11:46:11 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

void	populate_from_environment(t_memptr *memptr)
{
	char	*path;

	memptr->my_pwd = ft_strdup(getenv("PWD"));
	if (!memptr->my_pwd)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	memptr->my_oldpwd = ft_strdup(getenv("OLDPWD"));
	if (!memptr->my_oldpwd)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	path = getenv("PATH");
	if (!memptr->my_pwd || !memptr->my_oldpwd || !path)
		exit_error(ENV_ERROR, *memptr, NULL);
	memptr->path_list = ft_split(getenv("PATH"), ':');
	if (!(memptr->path_list))
		exit_error(MALLOC_ERROR, *memptr, NULL);
}

void	bash_main(t_memptr *memptr)
{
	g_status_flag = 0;
	update_shell_level(&memptr->envp, memptr);
	populate_from_environment(memptr);
	while (g_status_flag != EOF_SIGNAL)
	{
		set_signal();
		bash_run(memptr->envp, memptr);
		clean_memory(memptr);
		update_path(memptr);
	}
	clean_memory(memptr);
	ft_free_tabs((void **)(memptr->envp));
	if (memptr->my_pwd)
		free(memptr->my_pwd);
	if (memptr->my_oldpwd)
		free(memptr->my_oldpwd);
}
