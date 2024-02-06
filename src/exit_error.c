/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 18:15:46 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *error_msg, t_memptr memptr, char *extra_error_msg)
{
	t_env	*envv;

	non_exit_error(error_msg, memptr, extra_error_msg);
	envv = get_envv();
	free_envv(envv);
	clean_memory(memptr);
	if (*memptr.envp)
		ft_free_tabs((void **)memptr.envp);
	exit(g_status_flag);
}

// Alterado para utilizar perror em vez de ft_fprintf
void	non_exit_error(char *error_msg, t_memptr memptr, char *extra_error_msg)
{
	char	*message;

	set_g_status_flag(error_msg);
	if (!ft_strcmp(error_msg, OPEN_ERROR)
		|| !ft_strcmp(error_msg, PERMISSION_ERROR))
		perror(extra_error_msg);
	else if (!ft_strcmp(error_msg, QUOTE_ERROR)
		|| !ft_strcmp(error_msg, SYNTAX_ERROR)
		|| !ft_strcmp(error_msg, EOF_ERROR))
		printf(error_msg, NULL);
	else if (!ft_strcmp(error_msg, DIRECTORY_ERROR)
		|| !ft_strcmp(error_msg, COMMAND_ERROR))
	{
		message = ft_strjoin(extra_error_msg, error_msg);
		if (!message)
			exit_error(MALLOC_ERROR, memptr, NULL);
		printf(message, NULL);
	}
	else
		perror(NULL);
}

void	set_g_status_flag(char *error_msg)
{
	if (!ft_strcmp(error_msg, EOF_ERROR))
		g_status_flag = 0;
	else if (!ft_strcmp(error_msg, OPEN_ERROR))
		g_status_flag = 1;
	else if (!ft_strcmp(error_msg, SYNTAX_ERROR))
		g_status_flag = 2;
	else if (!ft_strcmp(error_msg, PERMISSION_ERROR)
		|| !ft_strcmp(error_msg, DIRECTORY_ERROR))
		g_status_flag = 126;
	else if (!ft_strcmp(error_msg, COMMAND_ERROR))
		g_status_flag = 127;
}
