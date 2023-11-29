/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 12:23:12 by mde-sa--         ###   ########.fr       */
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
		if ((*lst)->input_target)
			free((*lst)->input_target);
		if ((*lst)->heredoc_buffer)
			free((*lst)->heredoc_buffer);
		if ((*lst)->full_output)
			ft_free_tabs((void **)(*lst)->full_output);
		if ((*lst)->output_target)
			free((*lst)->output_target);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
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
		ft_free_tabs((void **)memptr.pipe_fd);
}

void	exit_error(char *error_message, t_memptr memptr, ...)
{
	va_list args;
	va_start(args, memptr);
	if (!ft_strcmp(error_message, COMMAND_ERROR))
		ft_fprintf(STDERR_FILENO,
			"%s: command not found\n", va_arg(args, char *));
	else
		perror(error_message);
	va_end(args);
	clean_memory(memptr);
	exit(0);
}
