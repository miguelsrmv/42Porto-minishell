/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:04:47 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/03 17:38:40 by mde-sa--         ###   ########.fr       */
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
		if ((*lst)->heredoc_buffer)
			free((*lst)->heredoc_buffer);
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

void	final_clear_and_exit(t_memptr memptr, char **envp)
{
	clean_memory(memptr);
	free_envv(get_envv());
	ft_free_tabs((void **)envp);
	exit(g_status_flag);
}
