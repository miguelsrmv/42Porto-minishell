/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_input_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:24:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/26 00:40:01 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	input_check(t_command_table **command, t_memptr *memptr)
{
	enum e_ValidType	input_status;

	input_status = check_input(command);
	if (input_status == VALID)
		return (TRUE);
	else if (input_status == INVALID_INPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, *memptr, NULL);
	else if (input_status == INVALID_INPUT)
		non_exit_error(OPEN_ERROR, *memptr, (*command)->input_target);
	else if (input_status == INVALID_INPUT_READ)
		non_exit_error(PERMISSION_IO_ERROR, *memptr, (*command)->input_target);
	else if (input_status == EMPTY)
		non_exit_error(EMPTY_ERROR, *memptr, NULL);
	return (FALSE);
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

enum e_ValidType	input_target_check(char *target)
{
	if (ft_strlen(target) == 0)
		return (EMPTY);
	else if (access(target, F_OK) != 0)
		return (INVALID_INPUT);
	else if (access(target, R_OK) != 0)
		return (INVALID_INPUT_READ);
	else
		return (VALID);
}
