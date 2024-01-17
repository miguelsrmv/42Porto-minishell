/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/17 15:41:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_lexer_list(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->token)
			free((*lst)->token);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

// Comentado porque dava double free

void	clear_command_table(t_command_table **lst)
{
	t_command_table	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd)
			ft_free_tabs((void **)(*lst)->cmd);
		if ((*lst)->cmd_target)
			free((*lst)->cmd_target);
		if ((*lst)->full_input)
			ft_free_tabs((void **)(*lst)->full_input);
/*  	if ((*lst)->input_target)
			free((*lst)->input_target); */
		if ((*lst)->heredoc_buffer)
			free((*lst)->heredoc_buffer);
		if ((*lst)->full_output)
			ft_free_tabs((void **)(*lst)->full_output);
/* 		if ((*lst)->output_target)
			free((*lst)->output_target); */
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	close_pipes_error(int **pipe)
{
	int	i;

	i = 0;
	while (pipe[i])
	{
		close(pipe[i][0]);
		close(pipe[i][i]);
		i++;
	}
}

void	clean_memory(t_memptr memptr)
{
	if (memptr.lexer_list)
		clear_lexer_list(memptr.lexer_list);
	if (memptr.command_table)
		clear_command_table(memptr.command_table);
	if (memptr.path_list)
		ft_free_tabs((void **)memptr.path_list);
	if (memptr.pipe_fd)
	{
		close_pipes_error(memptr.pipe_fd);
		ft_free_tabs((void **)memptr.pipe_fd);
	}
}

void	exit_error(char *error_msg, t_memptr memptr, ...)
{
	va_list	args;
	t_env	*envv;

	va_start(args, memptr);
	if (!ft_strcmp(error_msg, COMMAND_ERROR)
		|| !ft_strcmp(error_msg, OPEN_ERROR))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s", va_arg(args, char *), error_msg);
		g_status_flag = 1;
	}
	else if (!ft_strcmp(error_msg, DIRECTORY_ERROR))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s", &va_arg(args, char *)[2],
			error_msg);
		g_status_flag = 127;
	}
	else if (!ft_strcmp(error_msg, SYNTAX_ERROR)
		|| !ft_strcmp(error_msg, QUOTE_ERROR)
		|| !ft_strcmp(error_msg, EOF_ERROR))
		exit(g_status_flag);
	else
		perror(error_msg);
	va_end(args);
	envv = get_envv();
	free_envv(envv);
	clean_memory(memptr);
	if (*memptr.envp)
		ft_free_tabs((void **)memptr.envp);
	exit(g_status_flag);
}
