/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redir_setter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:46:53 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/18 22:19:08 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_input_redir(int **pipe_fd, t_command_table **command,
			t_memptr memptr)
{
	if ((*command)->input_type == INPUT || (*command)->input_type == HERE_DOC)
	{
		(*command)->input_fd = open((*command)->input_target, O_RDONLY);
		if ((*command)->input_fd == -1)
			exit_error(OPEN_ERROR, memptr);
	}
	else if ((*command)->input_type == PIPE)
		(*command)->input_fd = pipe_fd[(*command)->command_no - 2][0];
	if ((*command)->input_type != NULL_REDIRECT)
	{
		if (dup2((*command)->input_fd, STDIN_FILENO) == -1)
			exit_error(DUP_ERROR, memptr);
	}
	if ((*command)->input_type == HERE_DOC)
	{
		if (unlink((*command)->heredoc_buffer) == -1)
			exit_error(UNLINK_ERROR, memptr);
	}
}

void	set_output_redir(int **pipe_fd, t_command_table **command,
			t_memptr memptr)
{
	if ((*command)->output_type == OUTPUT)
	{
		(*command)->output_fd = open((*command)->output_target,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*command)->output_fd == -1)
			exit_error(OPEN_ERROR, memptr);
	}
	else if ((*command)->output_type == APPEND)
	{
		(*command)->output_fd = open((*command)->output_target,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*command)->output_fd == -1)
			exit_error(OPEN_ERROR, memptr);
	}
	else if ((*command)->output_type == PIPE)
		(*command)->output_fd = pipe_fd[(*command)->command_no - 1][1];
	if ((*command)->output_type != NULL_REDIRECT)
	{
		if (dup2((*command)->output_fd, STDOUT_FILENO) == -1)
			exit_error(DUP_ERROR, memptr);
	}
}

void	close_redir_pipes(int **pipe_fd, t_command_table **command,
			t_memptr memptr)
{
	if (!pipe_fd)
		return ;
	if ((*command)->command_no > 1)
	{
		if (close(pipe_fd[(*command)->command_no - 2][0]) == -1)
			exit_error(CLOSE_ERROR, memptr);
	}
	if ((*command)->next)
	{
		if (close(pipe_fd[(*command)->command_no - 1][1]) == -1)
			exit_error(CLOSE_ERROR, memptr);
	}
}
