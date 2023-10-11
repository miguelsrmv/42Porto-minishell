/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 12:34:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_error(char *error_message)
{
	ft_printf(error_message);
	exit(0);
}

int ft_tab_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

int	main(void)
{
	char *buffer;
	char **lexer;
	
	buffer = readline("minishell$: ");
    lexer = readline_split(buffer);

	ft_printf("\n *** BEFORE PARSING *** \n");
    for (int i = 0; lexer[i]; i++)
		printf("%s\n", lexer[i]);
	ft_printf("\n");

	if (!parser(lexer, (int)ft_tab_len(lexer)))
	{
		ft_printf("ERROR!");
		return (0);
	}

	ft_printf("\n *** AFTER PARSING *** \n");
    for (int i = 0; lexer[i]; i++)
		printf("%s\n", lexer[i]);
	ft_printf("\n");
	/*
	// Get string from readline (include readline)

	ft_printf("\nYou typed in \"%s\".\n\n", buffer);

	// Splits buffer, ignoring quotes
	char **splitted_buffer;
	splitted_buffer = ft_command_split(buffer);
	ft_printf("List of words:\n");
	while (*splitted_buffer)
	{
		ft_printf("%s\n", *splitted_buffer);
		splitted_buffer++;
	}

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
