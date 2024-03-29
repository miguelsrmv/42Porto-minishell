/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:53:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 11:32:27 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_parent(char **buffer, int *pipe_fd,
			t_memptr memptr, enum e_QuoteType quote_status)
{
	if (*buffer)
		free(*buffer);
	*buffer = calloc(1, sizeof(char));
	while (waitpid(0, &g_status_flag, 0) > 0)
		continue ;
	if (WIFEXITED(g_status_flag))
		g_status_flag = WEXITSTATUS(g_status_flag);
	if (g_status_flag != 8)
	{
		while (TRUE)
			if (!read_from_pipe(pipe_fd[0], buffer,
					memptr, quote_status))
				break ;
	}
	close(pipe_fd[0]);
}

int	read_from_pipe(int read_fd, char **buffer,
			t_memptr memptr, enum e_QuoteType quote_status)
{
	size_t	sizeoftemp_buffer;
	char	*temp_buffer;
	char	*temp;

	if (read(read_fd, &sizeoftemp_buffer, sizeof(size_t)) <= 0)
		return (0);
	temp_buffer = (char *)malloc((sizeoftemp_buffer + 2) * sizeof(char));
	if (!temp_buffer)
		exit_error(MALLOC_ERROR, memptr, NULL);
	read(read_fd, temp_buffer, sizeoftemp_buffer + 1);
	temp_buffer[sizeoftemp_buffer + 1] = '\0';
	expand_buffer(&temp_buffer, memptr, quote_status);
	temp = *buffer;
	*buffer = ft_strjoin(*buffer, temp_buffer);
	free(temp);
	free(temp_buffer);
	return (1);
}
