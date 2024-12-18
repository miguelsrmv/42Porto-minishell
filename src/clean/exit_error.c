/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/25 10:57:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *error, t_memptr memptr, char *extra_error)
{
	set_g_status_flag(error);
	non_exit_error(error, memptr, extra_error);
	clean_memory(&memptr);
	final_clear_and_exit(memptr, memptr.envp, memptr.pipe_fd,
		*(memptr.command_table));
}

void	non_exit_error(char *error, t_memptr memptr, char *extra_error)
{
	char	*message;

	set_g_status_flag(error);
	if (!ft_strcmp(error, OPEN_ERROR) || !ft_strcmp(error, PERMISSION_ERROR))
		perror(extra_error);
	else if (!ft_strcmp(error, EMPTY_INPUT_ERROR) || !ft_strcmp(error,
			QUOTE_ERROR) || !ft_strcmp(error, EOF_ERROR) || !ft_strcmp(error,
			SYNTAX_ERROR) || !ft_strcmp(error, S_EOF) || !ft_strcmp(error,
			EMPTY_ERROR) || !ft_strcmp(error, ENV_ERROR))
		printf(error, NULL);
	else if (!ft_strcmp(error, DIRECTORY_ERROR) || !ft_strcmp(error,
			COMMAND_ERROR) || !ft_strcmp(error, DIRECTORY_OUTPUT_ERROR)
		|| !ft_strcmp(error, DIR_OPEN_ERROR) || !ft_strcmp(error,
			NOT_A_DIR_ERROR) || !ft_strcmp(error, PERMISSION_IO_ERROR))
	{
		message = ft_strjoin(extra_error, error);
		if (!message)
			exit_error(MALLOC_ERROR, memptr, NULL);
		printf(message, NULL);
		ft_free_str(&message);
	}
	else
		perror(NULL);
}

void	set_g_status_flag(char *error)
{
	if (!ft_strcmp(error, EOF_ERROR))
		g_status_flag = 0;
	else if (!ft_strcmp(error, OPEN_ERROR) || !ft_strcmp(error, EMPTY_ERROR)
		|| !ft_strcmp(error, DIRECTORY_OUTPUT_ERROR) || !ft_strcmp(error,
			PERMISSION_IO_ERROR))
		g_status_flag = 1;
	else if (!ft_strcmp(error, SYNTAX_ERROR) || !ft_strcmp(error, QUOTE_ERROR))
		g_status_flag = 2;
	else if (!ft_strcmp(error, PERMISSION_ERROR) || !ft_strcmp(error,
			DIRECTORY_ERROR) || !ft_strcmp(error, NOT_A_DIR_ERROR))
		g_status_flag = 126;
	else if (!ft_strcmp(error, COMMAND_ERROR) || !ft_strcmp(error,
			DIR_OPEN_ERROR))
		g_status_flag = 127;
}
