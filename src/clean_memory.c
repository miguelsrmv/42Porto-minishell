/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:04:47 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/30 14:27:38 by mde-sa--         ###   ########.fr       */
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