/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:53:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 16:15:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_parent(char **buffer, int *pipe_fd, t_memptr memptr)
{
	size_t	sizeoftemp_buffer;
	char	*temp_buffer;

	*buffer = calloc(1, sizeof(char));
	while (waitpid(0, &g_status_flag, 0) > 0)
		continue ;
	if (WIFEXITED(g_status_flag))
		g_status_flag = WEXITSTATUS(g_status_flag);
	if (g_status_flag != SIGINT)
	{
		while (TRUE)
		{
			if (read(pipe_fd[0], &sizeoftemp_buffer, sizeof(size_t)) <= 0)
				break;
			temp_buffer = (char *)malloc((sizeoftemp_buffer + 2) * sizeof(char));
			if (!temp_buffer)
				exit_error(MALLOC_ERROR, memptr, NULL);
			read(pipe_fd[0], temp_buffer, sizeoftemp_buffer + 1);
			temp_buffer[sizeoftemp_buffer + 1] = '\0';
			*buffer = ft_strjoin(*buffer, temp_buffer);
			free(temp_buffer);
		}
	}
	close(pipe_fd[0]);
}
