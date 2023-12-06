/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/05 14:03:04 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*set_environment_vars(char **envp, t_memptr memptr)
{
	t_env			*envv;

	envv = init_envv(envp);
	if (envv == NULL)
		exit_error(ENV_ERROR, memptr);
	//set_envp(envp);
	set_envv(envv);
	return (envv);
}

int	main(int argc, char **argv, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	t_memptr		memptr;
	t_env			*envv;

	(void)argv;
	lexer_list = NULL;
	command_table = NULL;
	memptr = initialize_memptr(&lexer_list, &command_table);
	if (argc >10) // Mudar no fim
		exit_error(USAGE_ERROR, memptr);
	envv = set_environment_vars(envp, memptr);
	while (TRUE)
	{
		lexer_list = read_readline(memptr);
		command_table = parse_list(lexer_list, memptr);
		expand_command_table(&command_table, memptr);
		prepare_processes(&command_table, &envv, memptr);
		clean_memory(memptr);
	}
/* 	lexer_list = read_readline(memptr);
	command_table = parse_list(lexer_list, memptr);
	expand_command_table(&command_table, memptr);
	prepare_processes(&command_table, envp, memptr);
	clean_memory(memptr);
	return (0); */
}
