/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redir_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:14:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/23 22:01:48 by mde-sa--         ###   ########.fr       */
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

enum e_ValidType	check_output_directory(char *target)
{
	int		len;
	char	*path;

	len = ft_strlen(target) - 1;
	if (ft_strchr(target, '/'))
	{
		while (target[len] != '/')
			len--;
		path = ft_substr(target, 0, len);
		if (access(path, F_OK) != 0)
		{
			free(path);
			return (INVALID_OUTPUT);
		}
	}
	free(path);
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
		if (check_output_directory((*command)->output_target) == INVALID_OUTPUT)
			return (INVALID_OUTPUT);
	}
	if ((*command)->next && (*command)->output_type != OUTPUT
		&& (*command)->output_type != APPEND)
		(*command)->output_type = PIPE;
	if (!(*command)->output_target && (*command)->output_type != PIPE)
		(*command)->output_type = NULL_REDIRECT;
	return (VALID);
}

// Transformar caso de INVALID_INPUT em non-exit-error!!!!
// Apagar (null) em caso de Invalid output (criar exit específico ???)
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

enum e_ValidType	non_exit_check_redirections(int **pipe_fd, t_command_table **command,
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
