/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/13 13:16:55 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_SignalType	g_signal_flag = NO_SIGNAL;

t_memptr	initialize_memptr(t_token **lexer_list,
				t_command_table **command_table,
				char **argv, char **envp)
{
	t_memptr	memptr;

	memptr.lexer_list = lexer_list;
	memptr.command_table = command_table;
	memptr.path_list = NULL;
	memptr.pipe_fd = NULL;
	memptr.argv = argv;
	memptr.envp = envp;
	memptr.return_value = 0;
	return (memptr);
}

int	main(int argc, char **argv, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	t_memptr		memptr;
	char			**envp_cpy;

	if (argc > 10) // mudar depois
		exit_error(USAGE_ERROR, memptr);
	lexer_list = NULL;
	command_table = NULL;
	envp_cpy = ft_tabdup(envp);
	memptr = initialize_memptr(&lexer_list, &command_table, argv, envp_cpy);
	bash_main(envp_cpy, &memptr);
	ft_free_tabs((void**)envp);
	return (0);
}
