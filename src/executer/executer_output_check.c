/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_output_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:43:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/28 13:49:00 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	output_check(t_command_table **command, t_memptr *memptr)
{
	enum e_ValidType	output_status;

	output_status = check_output(command, *memptr);
	if (output_status == VALID)
		return (TRUE);
	else if (output_status == INVALID_OUTPUT)
		non_exit_error(DIRECTORY_OUTPUT_ERROR,
			*memptr, (*command)->output_target);
	else if (output_status == INVALID_OUTPUT_REDIR)
		non_exit_error(SYNTAX_ERROR, *memptr, NULL);
	else if (output_status == INVALID_OUTPUT_WRITE)
		non_exit_error(PERMISSION_IO_ERROR, *memptr, (*command)->output_target);
	else if (output_status == EMPTY)
		non_exit_error(EMPTY_ERROR, *memptr, NULL);
	return (FALSE);
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
		g_status_flag = 0;
	}
	if ((*command)->next && (*command)->output_type != OUTPUT
		&& (*command)->output_type != APPEND)
		(*command)->output_type = PIPE;
	if (!(*command)->output_target && (*command)->output_type != PIPE)
		(*command)->output_type = NULL_REDIRECT;
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

void	create_output(enum e_RedirectType input_type, char	*target,
			t_memptr memptr)
{
	int	fd;

	fd = 0;
	if (input_type == OUTPUT)
		fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (input_type == APPEND)
		fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_error(OPEN_ERROR, memptr, NULL);
	if (close(fd) == -1)
		exit_error(CLOSE_ERROR, memptr, NULL);
}
