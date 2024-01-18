/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redir_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:14:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/18 22:19:28 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_RedirectType	redir_check(char *redir_str)
{
	if (ft_strlen(redir_str) == 1 && !ft_strncmp("<", redir_str, 1))
		return (INPUT);
	else if (ft_strlen(redir_str) == 2 && !ft_strncmp("<<", redir_str, 2))
		return (HERE_DOC);
	else if (ft_strlen(redir_str) == 1 && !ft_strncmp(">", redir_str, 1))
		return (OUTPUT);
	else if (ft_strlen(redir_str) == 2 && ! ft_strncmp(">>", redir_str, 2))
		return (APPEND);
	else
		return (INVALID);
}

enum e_ValidType	check_input(t_command_table **command)
{
	int	i;

	i = 0;
	while ((*command)->full_input[i])
	{
		if (redir_check((*command)->full_input[i]) != INVALID)
			(*command)->input_type
				= redir_check((*command)->full_input[i++]);
		else
			return (INVALID_INPUT_REDIR);
		(*command)->input_target = (*command)->full_input[i++];
		if ((*command)->input_type == INPUT
			&& access((*command)->input_target, F_OK) != 0)
			return (INVALID_INPUT);
	}
	if ((*command)->input_type == HERE_DOC)
		(*command)->input_target = (*command)->heredoc_buffer;
	if ((*command)->command_no != 1 && (*command)->input_type != INPUT
		&& (*command)->input_type != HERE_DOC)
		(*command)->input_type = PIPE;
	if (!(*command)->input_target && (*command)->input_type != PIPE)
		(*command)->input_type = NULL_REDIRECT;
	return (VALID);
}

enum e_ValidType	check_output(t_command_table **command)
{
	int	i;

	i = 0;
	while ((*command)->full_output[i])
	{
		if (redir_check((*command)->full_output[i]) != INVALID)
			(*command)->output_type
				= redir_check((*command)->full_output[i++]);
		else
			return (INVALID_OUTPUT_REDIR);
		(*command)->output_target = (*command)->full_output[i++];
	}
	if ((*command)->next && (*command)->output_type != OUTPUT
		&& (*command)->output_type != APPEND)
		(*command)->output_type = PIPE;
	if (!(*command)->output_target && (*command)->output_type != PIPE)
		(*command)->output_type = NULL_REDIRECT;
	return (VALID);
}

// Transformar caso de INVALID_INPUT em non-exit-error!!!!
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
	else if (output_status == INVALID_OUTPUT_REDIR)
		exit_error(SYNTAX_ERROR, memptr);
	return (VALID);
}
