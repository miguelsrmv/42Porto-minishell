/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 12:52:37 by mde-sa--         ###   ########.fr       */
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

void	non_exit_error(char *error_msg, t_memptr memptr, char *extra_error_msg)
{
	(void)memptr;
	set_g_status_flag(error_msg);
	if (!ft_strcmp(error_msg, OPEN_ERROR)
		|| !ft_strcmp(error_msg, PERMISSION_ERROR)
		|| !ft_strcmp(error_msg, DIRECTORY_ERROR)
		|| !ft_strcmp(error_msg, COMMAND_ERROR))
		print_to_fd(STDERR_FILENO, error_msg, extra_error_msg,
			memptr);
	else if (!ft_strcmp(error_msg, QUOTE_ERROR)
		|| !ft_strcmp(error_msg, EOF_ERROR)
		|| !ft_strcmp(error_msg, SYNTAX_ERROR))
		print_to_fd(STDERR_FILENO, error_msg, NULL, memptr);
	else
		perror(error_msg);
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

void	print_to_fd(int fd, char *error_msg, char *extra_error_msg,
			t_memptr memptr)
{
	int	old_stdout;

	old_stdout = dup(STDOUT_FILENO);
	if (old_stdout == -1)
		exit_error(DUP_ERROR, memptr, NULL);
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_error(DUP_ERROR, memptr, NULL);
	if (extra_error_msg)
		printf("%s: %s", error_msg, extra_error_msg);
	else
		printf("%s", error_msg);
	if (dup2(old_stdout, STDOUT_FILENO) == -1)
		exit_error(DUP_ERROR, memptr, NULL);
	close(old_stdout);
}
