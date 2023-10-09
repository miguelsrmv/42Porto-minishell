/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/09 10:31:47 by mde-sa--         ###   ########.fr       */
=======
/*   Updated: 2023/09/29 16:53:23 by mde-sa--         ###   ########.fr       */
>>>>>>> 89d7bb5d16303f25fca900a2c273fc19aa0f4c1b
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
<<<<<<< HEAD
	// Get string from readline (include readline)
	char *buffer;
=======
	char	*buffer;

>>>>>>> 89d7bb5d16303f25fca900a2c273fc19aa0f4c1b
	buffer = readline("minishell$: ");
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
	
}
