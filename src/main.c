/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/18 21:55:32 by mde-sa--         ###   ########.fr       */
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
	t_error			error;

	lexer_list = NULL;
	command_table = NULL;
	error.lexer_list = lexer_list;
	error.command_table = command_table;
	while (1)
	{
		lexer_list = read_readline(error);
		command_table = parse_list(lexer_list, error);
		expand_command_table(&command_table);
		prepare_processes(&command_table, envp);
	}
	return (argc);
}
