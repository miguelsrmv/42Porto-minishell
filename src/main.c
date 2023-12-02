/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/02 23:34:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_SignalType signal_flag = NO_SIGNAL;

t_memptr	initialize_memptr(t_token **lexer_list,
				t_command_table **command_table)
{
	t_memptr	memptr;

	memptr.lexer_list = lexer_list;
	memptr.command_table = command_table;
	memptr.path_list = NULL;
	memptr.pipe_fd = NULL;
	return (memptr);
}

void	set_environment_vars(char **envp, t_memptr memptr)
{
	t_env			*envv;

	envv = init_envv(envp);
	if (envv == NULL)
		exit_error(ENV_ERROR, memptr);
	set_envp(envp);
	set_envv(envv);
}

int	main(int argc, char **argv, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	t_memptr		memptr;

	(void)argv;
	lexer_list = NULL;
	command_table = NULL;
	memptr = initialize_memptr(&lexer_list, &command_table);
	if (argc >10) // Mudar no fim
		exit_error(USAGE_ERROR, memptr);
	set_environment_vars(envp, memptr);
	bash_main(envp, memptr);
	return (0);
}
