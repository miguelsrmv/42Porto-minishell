/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:02:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/30 18:10:57 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredocs(t_command_table **command_table, t_memptr memptr)
{
	int	i;

	i = 0;
	while ((*command_table)->full_input[i])
	{
		if (ft_strlen((*command_table)->full_input[i]) == 2
			&& !ft_strncmp("<<", (*command_table)->full_input[i], 2))
		{
			if ((*command_table)->heredoc_buffer)
			{
				free((*command_table)->heredoc_buffer);
				(*command_table)->heredoc_buffer = NULL;
			}
			create_heredoc_buffer((*command_table)->full_input[i + 1],
				&(*command_table)->heredoc_buffer, memptr);
		}
		i = i + 2;
	}
	if ((*command_table)->heredoc_buffer)
		create_heredoc_file(command_table, (*command_table)->heredoc_buffer,
			memptr);
}

void	create_heredoc_buffer(char *delimiter, char **buffer, t_memptr memptr)
{
	int		bytes_read;
	char	input[1001];
	char	*temp;

	*buffer = ft_calloc(1, sizeof(char));
	if (!(*buffer))
		exit_error(MALLOC_ERROR, memptr);
	while (TRUE)
	{
		ft_printf("> ");
		bytes_read = read(STDIN_FILENO, input, 1000);
		if (bytes_read == -1 || bytes_read == 0)
			break ;
		input[bytes_read] = '\0';
		if (!ft_strcmp_input(input, delimiter))
			break ;
		temp = ft_strjoin(*buffer, input);
		if (!temp)
			exit_error(MALLOC_ERROR, memptr);
		free(*buffer);
		*buffer = temp;
	}
}

void	create_heredoc_file(t_command_table **command_table,
			char *buffer, t_memptr memptr)
{
	char	*name;
	int		i;
	int		fd;

	i = 0;
	while (TRUE)
	{
		name = ft_itoa(i);
		if (access(name, F_OK) != 0)
			break ;
		free(name);
		i++;
	}
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(OPEN_ERROR, memptr, name);
	if (write(fd, buffer, ft_strlen(buffer)) == -1)
		exit_error(WRITE_ERROR, memptr);
	if (close(fd) == -1)
		exit_error(CLOSE_ERROR, memptr);
	free(buffer);
	(*command_table)->heredoc_buffer = name;
}
