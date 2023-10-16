/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/16 17:24:32 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_error(char *error_message)
{
	ft_printf(error_message);
	exit(0);
}

int	main(void)
{
	int		i;
	t_token	*lexer_list;
	t_token	*current;

    lexer_list = read_readline();
	current = lexer_list;
	i = 1;
	while (current)
	{
		if (current->token)
			ft_printf("Node %i: %s\n", i++, current->token);
		current = current->next;
	}

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
