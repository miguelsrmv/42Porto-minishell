/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redir_checker2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:00:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/02 22:49:06 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_ValidType	check_redirections(int **pipe_fd, t_command_table **command,
			t_memptr memptr)
{
	enum e_ValidType	input_status;
	enum e_ValidType	output_status;

	input_status = check_input(command);
	output_status = check_output(command);
	if (input_status == VALID && output_status == VALID)
	{
		set_input_redir(pipe_fd, command, memptr);
		set_output_redir(pipe_fd, command, memptr);
		close_redir_pipes(pipe_fd, command, memptr);
		return (VALID);
	}
	else if (input_status == INVALID_INPUT_REDIR)
		exit_error(SYNTAX_ERROR, memptr);
	else if (input_status == INVALID_INPUT)
		exit_error(OPEN_ERROR, memptr, (*command)->input_target);
	else if (output_status == INVALID_OUTPUT)
		exit_error(OPEN_ERROR, memptr, (*command)->output_target);
	else if (output_status == INVALID_OUTPUT_REDIR)
		exit_error(SYNTAX_ERROR, memptr);
	return (VALID);
}

enum e_ValidType	non_exit_check_redirections(int **pipe_fd,
			t_command_table **command, t_memptr memptr)
{
	enum e_ValidType	input_status;
	enum e_ValidType	output_status;

	input_status = check_input(command);
	output_status = check_output(command);
	if (input_status == VALID && output_status == VALID)
	{
		set_input_redir(pipe_fd, command, memptr);
		set_output_redir(pipe_fd, command, memptr);
		close_redir_pipes(pipe_fd, command, memptr);
		return (VALID);
	}
	else if (input_status == INVALID_INPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, memptr);
	else if (input_status == INVALID_INPUT)
		non_exit_error(OPEN_ERROR, memptr, (*command)->input_target);
	else if (output_status == INVALID_OUTPUT)
		non_exit_error(OPEN_ERROR, memptr, (*command)->output_target);
	else if (output_status == INVALID_OUTPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, memptr);
	if (input_status != VALID)
		return (input_status);
	else
		return (output_status);
}
