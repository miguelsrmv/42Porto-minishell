/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/27 22:21:47 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
}

int	main(int argc, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	t_memptr		memptr;

	if (argc == 0)
		exit_error(USAGE_ERROR, memptr);
	lexer_list = NULL;
	command_table = NULL;
	memptr.lexer_list = &lexer_list;
	memptr.command_table = &command_table;
 	while (1)
	{
		lexer_list = read_readline(memptr);
		command_table = parse_list(lexer_list, memptr);
		expand_command_table(&command_table, memptr);
		prepare_processes(&command_table, envp, memptr);
		clean_memory(memptr);
	}
	return (0);
}
