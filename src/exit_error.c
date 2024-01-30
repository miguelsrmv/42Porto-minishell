/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/30 14:23:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *error_msg, t_memptr memptr, ...)
{
	va_list	args;
	t_env	*envv;

	va_start(args, memptr);
	non_exit_error(error_msg, memptr, va_arg(args, char *));
	va_end(args);
	envv = get_envv();
	free_envv(envv);
	clean_memory(memptr);
	if (*memptr.envp)
		ft_free_tabs((void **)memptr.envp);
	exit(g_status_flag);
}

void	non_exit_error(char *error_msg, t_memptr memptr, ...)
{
	va_list	args;

	va_start(args, memptr);
	set_g_status_flag(error_msg);
	if (!ft_strcmp(error_msg, OPEN_ERROR)
		|| !ft_strcmp(error_msg, PERMISSION_ERROR)
		|| !ft_strcmp(error_msg, DIRECTORY_ERROR)
		|| !ft_strcmp(error_msg, COMMAND_ERROR)
		|| !ft_strcmp(error_msg, SYNTAX_ERROR))
		ft_fprintf(STDERR_FILENO, "%s: %s", va_arg(args, char *), error_msg);
	else if (!ft_strcmp(error_msg, QUOTE_ERROR)
		|| !ft_strcmp(error_msg, EOF_ERROR))
		ft_fprintf(STDERR_FILENO, "%s", error_msg);
	else
		perror(error_msg);
	va_end(args);
}

void	set_g_status_flag(char *error_msg)
{
	if (!ft_strcmp(error_msg, OPEN_ERROR))
		g_status_flag = 1;
	else if (!ft_strcmp(error_msg, SYNTAX_ERROR))
		g_status_flag = 2;
	else if (!ft_strcmp(error_msg, PERMISSION_ERROR)
		|| !ft_strcmp(error_msg, DIRECTORY_ERROR))
		g_status_flag = 126;
	else if (!ft_strcmp(error_msg, COMMAND_ERROR))
		g_status_flag = 127;
}
