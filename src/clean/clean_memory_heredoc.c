/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:52:13 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/28 16:57:31 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_command_table_heredoc(t_command_table **lst)
{
	t_command_table	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd)
			ft_free_tabs((void **)(*lst)->cmd);
		if ((*lst)->cmd_before_expansion)
			ft_free_tabs((void **)(*lst)->cmd_before_expansion);
		if ((*lst)->cmd_target)
			free((*lst)->cmd_target);
		if ((*lst)->full_input)
			ft_free_tabs((void **)(*lst)->full_input);
		if ((*lst)->heredoc_buffer)
			free((*lst)->heredoc_buffer);
		if ((*lst)->full_output)
			ft_free_tabs((void **)(*lst)->full_output);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	clean_memory_heredoc(t_memptr *memptr)
{
	if (memptr->lexer_list)
		clear_lexer_list(memptr->lexer_list);
	if (memptr->command_table)
		clear_command_table_heredoc(memptr->command_table);
	if (memptr->first_node)
		clear_command_table_heredoc(memptr->first_node);
	if (memptr->path_list)
	{
		ft_free_tabs((void **)memptr->path_list);
		memptr->path_list = NULL;
	}
	if (memptr->pipe_fd)
	{
		close_pipes_error(memptr->pipe_fd);
		ft_free_tabs((void **)memptr->pipe_fd);
		memptr->pipe_fd = NULL;
	}
}
