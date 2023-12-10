/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/10 10:33:27 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_SignalType	g_signal_flag = NO_SIGNAL;

t_memptr	initialize_memptr(t_token **lexer_list,
				t_command_table **command_table,
					char **envp_cpy)
{
	t_memptr	memptr;

	memptr.lexer_list = lexer_list;
	memptr.command_table = command_table;
	memptr.envp_cpy = envp_cpy;
	memptr.path_list = NULL;
	memptr.pipe_fd = NULL;
	memptr.envp_pipe = NULL;
	return (memptr);
}

int	main(int argc, char **argv, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	char			**envp_cpy;
	t_memptr		memptr;

	(void)argv;
	if (argc > 10) // mudar depois
		exit_error(USAGE_ERROR, memptr);
	lexer_list = NULL;
	command_table = NULL;
	envp_cpy = ft_tabdup(envp);
	if (!envp_cpy)
		exit_error(MALLOC_ERROR, memptr);
	memptr = initialize_memptr(&lexer_list, &command_table, envp_cpy);
	bash_main(envp_cpy, memptr);
	ft_free_tabs((void **)envp_cpy);
	return (0);
}
