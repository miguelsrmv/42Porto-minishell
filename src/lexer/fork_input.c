/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:19:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/21 23:38:53 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_child(int *pipe_fd, t_memptr memptr)
{
	char		*added_input;
	size_t		input_size;
	int			old_g_status_flag;

	old_g_status_flag = g_status_flag;
	g_status_flag = pipe_fd[1];
	added_input = readline("> ");
	if (!added_input)
	{
		close(pipe_fd[1]);
		g_status_flag = 2;
		exit_error(S_EOF, memptr, NULL);
	}
	input_size = ft_strlen(added_input);
	write(pipe_fd[1], &input_size, sizeof(size_t));
	write(pipe_fd[1], added_input, ft_strlen(added_input));
	write(pipe_fd[1], "\n", 1);
	free(added_input);
	close(pipe_fd[1]);
	finish_pipe_child(memptr, old_g_status_flag);
}

void	pipe_parent(char **input, int *pipe_fd, t_memptr memptr)
{
	while (waitpid(0, &g_status_flag, 0) > 0)
		continue ;
	if (WIFEXITED(g_status_flag))
		g_status_flag = WEXITSTATUS(g_status_flag);
	if (g_status_flag == 2)
	{
		free(*input);
		close(pipe_fd[0]);
		exit(g_status_flag);
	}
	else if (g_status_flag == 8)
	{
		free(*input);
		*input = NULL;
		g_status_flag = 130;
		close(pipe_fd[0]);
	}
	else
	{
		read_extra_input(pipe_fd[0], input, memptr);
		close(pipe_fd[0]);
	}
}

void	read_extra_input(int read_fd, char **input, t_memptr memptr)
{
	size_t	sizeoftemp_buffer;
	char	*temp_buffer;
	char	*temp;

	read(read_fd, &sizeoftemp_buffer, sizeof(size_t));
	temp_buffer = (char *)malloc((sizeoftemp_buffer + 2) * sizeof(char));
	if (!temp_buffer)
		exit_error(MALLOC_ERROR, memptr, NULL);
	read(read_fd, temp_buffer, sizeoftemp_buffer + 1);
	temp_buffer[sizeoftemp_buffer + 1] = '\0';
	temp = *input;
	*input = ft_strjoin(*input, temp_buffer);
	free(temp);
	free(temp_buffer);
}

void	finish_pipe_child(t_memptr memptr, int old_g_status_flag)
{
	t_env		*envv;

	g_status_flag = old_g_status_flag;
	envv = get_envv();
	free_envv(envv);
	clean_memory(memptr);
	if (*memptr.envp)
		ft_free_tabs((void **)memptr.envp);
	exit(old_g_status_flag);
}
