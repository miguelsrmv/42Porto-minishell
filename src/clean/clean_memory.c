/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:04:47 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 15:36:21 by mde-sa--         ###   ########.fr       */
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
		if ((*lst)->cmd_before_expansion)
			ft_free_tabs((void **)(*lst)->cmd_before_expansion);
		if ((*lst)->cmd_target)
			free((*lst)->cmd_target);
		if ((*lst)->full_input)
			ft_free_tabs((void **)(*lst)->full_input);
		if ((*lst)->heredoc_buffer)
		{
			unlink((*lst)->heredoc_buffer);
			free((*lst)->heredoc_buffer);
		}
		if ((*lst)->full_output)
			ft_free_tabs((void **)(*lst)->full_output);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	close_pipes_error(int **pipe)
{
	int	i;

	i = 0;
	{
		close(pipe[i][0]);
		close(pipe[i][i]);
		i++;
	}
}

void	clean_memory(t_memptr *memptr)
{
	if (memptr->lexer_list)
		clear_lexer_list(memptr->lexer_list);
	if (memptr->command_table)
		clear_command_table(memptr->command_table);
	if (memptr->first_node)
		clear_command_table(memptr->first_node);
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

void	final_clear_and_exit(t_memptr memptr, char **envp,
			int **pipe_fd, t_command_table *current)
{
	if (current)
	{
		if (current->command_no > 1)
			close(pipe_fd[current->command_no - 2][0]);
		if (current->next)
			close(pipe_fd[current->command_no - 1][1]);
		if (current->input_fd && current->input_type != PIPE)
			close(current->input_fd);
		if (current->output_fd && current->output_type != PIPE)
			close(current->output_fd);
	}
	clean_memory(&memptr);
	free_envv(get_envv());
	ft_free_tabs((void **)envp);
	exit(g_status_flag);
}
