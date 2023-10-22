/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/22 12:48:03 by mde-sa--         ###   ########.fr       */
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



int	main(void)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	t_error			error;

	error.lexer_list = lexer_list;
	error.command_table = command_table;
	lexer_list = read_readline(error);
	command_table = parse_list(lexer_list, error);
	print_command_table(command_table);
	free_list(lexer_list);
	/*

	// Get current directory (include unistd & limits.h)
	char *current_dir;
	current_dir = NULL;	
	current_dir = getcwd(current_dir, PATH_MAX + 1);
	ft_printf("\nYou're on directory %s\n\n", current_dir);

	// Get list of PATHs (include stdlib)
	char *path;
	char **path_list;
	path = getenv("PATH");
	path_list = ft_split(path, ':');
	ft_printf("List of paths:\n");
	while (*path_list)
	{
		ft_printf("%s\n", *path_list);
		path_list++;
	}
	*/
}
