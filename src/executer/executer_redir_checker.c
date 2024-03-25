/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redir_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:14:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/25 14:37:40 by mde-sa--         ###   ########.fr       */
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
			(*command)->input_type = redir_check((*command)->full_input[i++]);
		else
			return (INVALID_INPUT_REDIR);
		(*command)->input_target = (*command)->full_input[i++];
		if ((*command)->input_type == INPUT
			&& input_target_check((*command)->input_target) != VALID)
			return (input_target_check((*command)->input_target));
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

enum e_ValidType	output_target_check(char *target)
{
	int			len;
	char		*path;
	struct stat	st;

	path = NULL;
	len = ft_strlen(target);
	if (len == 0)
		return (EMPTY);
	if (target[len - 1] == '/')
		len--;
	path = ft_substr(target, 0, len);
	if ((stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		|| (ft_last_char(target) == '/' && open(path, O_RDONLY) == -1))
	{
		free(path);
		return (INVALID_OUTPUT);
	}
	free(path);
	if (access(target, F_OK) != -1 && access(target, W_OK) == -1)
		return (INVALID_OUTPUT_WRITE);
	return (VALID);
}

enum e_ValidType	check_output(t_command_table **command, t_memptr memptr)
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
		if (output_target_check((*command)->output_target) != VALID)
			return (output_target_check((*command)->output_target));
		create_output((*command)->output_type, (*command)->output_target,
			memptr);
	}
	if ((*command)->next && (*command)->output_type != OUTPUT
		&& (*command)->output_type != APPEND)
		(*command)->output_type = PIPE;
	if (!(*command)->output_target && (*command)->output_type != PIPE)
		(*command)->output_type = NULL_REDIRECT;
	return (VALID);
}

enum e_ValidType	input_target_check(char *target)
{
	if (access(target, F_OK) != 0)
		return (INVALID_INPUT);
	else if (ft_strlen(target) == 0)
		return (EMPTY);
	else if (access(target, R_OK) != 0)
		return (INVALID_INPUT_READ);
	else
		return (VALID);
}
