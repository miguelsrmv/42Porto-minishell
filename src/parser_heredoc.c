/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:02:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/23 19:27:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredocs(t_command_table **command_table)
{
	int	i;

	i = 0;
	while ((*command_table)->full_input[i])
	{
		if (ft_strlen((*command_table)->full_input[i]) == 2
			&& !ft_strncmp("<<", (*command_table)->full_input[i], 2))
			create_heredoc_buffer((*command_table)->full_input[i + 1],
				&(*command_table)->heredoc_buffer);
		i = i + 2;
	}
	if ((*command_table)->heredoc_buffer)
		create_heredoc_file(command_table, (*command_table)->heredoc_buffer);
}

void	create_heredoc_buffer(char *delimiter, char **buffer)
{
	int		bytes_read;
	char	input[1001];

	if (*buffer)
	{
		free (*buffer);
		*buffer = NULL;
	}
	*buffer = ft_calloc(1, sizeof(char));
	while (1)
	{
		ft_printf("> ");
		bytes_read = read(STDIN_FILENO, input, 1000);
		if (bytes_read == -1 || bytes_read == 0)
			break ;
		input[bytes_read] = '\0';
		if (!ft_strcmp_input(input, delimiter))
			break ;
		*buffer = ft_strjoin(*buffer, input);
		if (!(*buffer))
			break ; // error
	}
}

void	create_heredoc_file(t_command_table **command_table, char *buffer)
{
	char	*name;
	int		i;
	int		fd;

	i = 0;
	while (1)
	{
		name = ft_itoa(i);
		if (access(name, F_OK) != 0)
			break ;
		free(name);
		i++;
	}
	fd = open(name, O_WRONLY | O_CREAT, 0644);
	write(fd, buffer, sizeof(buffer));
	(*command_table)->heredoc_buffer = name;
}
