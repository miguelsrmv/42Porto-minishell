/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redir_checker2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:00:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/25 14:52:09 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_ValidType	check_redirections(int **pipe_fd, t_command_table **command,
			t_memptr memptr)
{
	enum e_ValidType	input_status;
	enum e_ValidType	output_status;

	input_status = check_input(command);
	output_status = check_output(command, memptr);
	if (input_status == VALID && output_status == VALID)
		return (set_redirs(pipe_fd, command, memptr));
	else if (input_status == INVALID_INPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, memptr, NULL);
	else if (input_status == INVALID_INPUT)
		non_exit_error(OPEN_ERROR, memptr, (*command)->input_target);
	else if (input_status == INVALID_INPUT_READ)
		non_exit_error(PERMISSION_IO_ERROR, memptr, (*command)->input_target);
	else if (output_status == INVALID_OUTPUT)
		non_exit_error(DIRECTORY_OUTPUT_ERROR,
			memptr, (*command)->output_target);
	else if (output_status == INVALID_OUTPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, memptr, NULL);
	else if (output_status == INVALID_OUTPUT_WRITE)
		non_exit_error(PERMISSION_IO_ERROR, memptr, (*command)->output_target);
	else if (input_status == EMPTY || output_status == EMPTY)
		non_exit_error(EMPTY_ERROR, memptr, NULL);
	if (input_status == VALID)
		return (output_status);
	return (input_status);
}

enum e_ValidType	non_exit_check_redirections(int **pipe_fd,
			t_command_table **command, t_memptr memptr)
{
	enum e_ValidType	input_status;
	enum e_ValidType	output_status;

	input_status = check_input(command);
	output_status = check_output(command, memptr);
	if (input_status == VALID && output_status == VALID)
		return (set_redirs(pipe_fd, command, memptr));
	else if (input_status == INVALID_INPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, memptr, NULL);
	else if (input_status == INVALID_INPUT)
		non_exit_error(OPEN_ERROR, memptr, (*command)->input_target);
	else if (input_status == INVALID_INPUT_READ)
		non_exit_error(PERMISSION_IO_ERROR, memptr, (*command)->input_target);
	else if (output_status == INVALID_OUTPUT)
		non_exit_error(DIRECTORY_OUTPUT_ERROR, memptr,
			(*command)->output_target);
	else if (output_status == INVALID_OUTPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, memptr, NULL);
	else if (output_status == INVALID_OUTPUT_WRITE)
		non_exit_error(PERMISSION_IO_ERROR, memptr, (*command)->output_target);
	else if (input_status == EMPTY || output_status == EMPTY)
		non_exit_error(EMPTY_ERROR, memptr, NULL);
	if (input_status == VALID)
		return (output_status);
	return (input_status);
}

/* void	create_all_other_outputs(t_command_table **command, t_memptr memptr)
{
	int				i;
	static int		fd;
	t_command_table	*current;

	current = *command;
	i = 0;
	fd = 0;
	while (current->full_output[i]
		&& (i < ft_tablen((void **)current->full_output) - 2))
	{
		if ((redir_check(current->full_output[i])) == OUTPUT)
			fd = open(current->full_output[i + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((redir_check(current->full_output[i])) == APPEND)
			fd = open(current->full_output[i + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		i = i + 2;
		if (fd == -1)
			exit_error(OPEN_ERROR, memptr, NULL);
		if (close(fd) == -1)
			exit_error(CLOSE_ERROR, memptr, NULL);
	}
} */

void	create_output(enum e_RedirectType input_type, char	*target,
			t_memptr memptr)
{
	int	fd;

	if (input_type == OUTPUT)
		fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (input_type == APPEND)
		fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_error(OPEN_ERROR, memptr, NULL);
	if (close(fd) == -1)
		exit_error(CLOSE_ERROR, memptr, NULL);
}

void	close_unused_output(t_command_table **command, t_memptr memptr)
{
	t_command_table	*current;

	current = *command;
	if (current->command_type != EXECUTABLE
		&& current->command_type != BUILTIN
		&& current->output_fd
		&& current->output_type != PIPE)
	{
		if (close(current->output_fd) == -1)
			exit_error(CLOSE_ERROR, memptr, NULL);
	}
}

enum e_ValidType	set_redirs(int **pipe_fd, t_command_table **command,
	t_memptr memptr)
{
	set_input_redir(pipe_fd, command, memptr);
	set_output_redir(pipe_fd, command, memptr);
	close_redir_pipes(pipe_fd, command, memptr);
	//create_all_other_outputs(command, memptr);
	close_unused_output(command, memptr);
	return (VALID);
}
