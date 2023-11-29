/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 08:45:06 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	t_memptr		memptr;

	lexer_list = NULL;
	command_table = NULL;
	memptr.lexer_list = &lexer_list;
	memptr.command_table = &command_table;
	if (argc == 0) // Mudar no fim
		exit_error(USAGE_ERROR, memptr);
	while (TRUE)
	{
		lexer_list = read_readline(memptr);
		command_table = parse_list(lexer_list, memptr);
		expand_command_table(&command_table, memptr);
		prepare_processes(&command_table, envp, memptr);
		clean_memory(memptr);
	}
	return (0);
}
