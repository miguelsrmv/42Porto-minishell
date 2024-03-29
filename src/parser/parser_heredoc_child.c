/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:56:11 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 14:46:44 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(char *delimiter, int *pipe_fd)
{
	char		*input;
	size_t		input_size;
	int			old_g_status_flag;

	old_g_status_flag = g_status_flag;
	g_status_flag = pipe_fd[1];
	while (TRUE)
	{
		input = readline("> ");
		if (!input)
		{
			close(pipe_fd[1]);
			ft_putstr_fd(S_EOF, STDERR_FILENO);
			return ;
		}
		if (!ft_strcmp(input, delimiter))
			break ;
		input_size = ft_strlen(input);
		write(pipe_fd[1], &input_size, sizeof(size_t));
		write(pipe_fd[1], input, ft_strlen(input));
		write(pipe_fd[1], "\n", 1);
		free(input);
	}
	close(pipe_fd[1]);
	g_status_flag = old_g_status_flag;
}

void	expand_buffer(char **buffer, t_memptr memptr,
			enum e_QuoteType quote_status)
{
	int	i;

	if (quote_status != OUT_QUOTE)
		return ;
	i = 0;
	while ((*buffer)[i])
	{
		if (((*buffer)[i] == '$' && (*buffer)[i + 1])
			&& ((*buffer)[i + 1]) == '?')
		{
			exit_value_expand(buffer, &i, memptr);
			i--;
		}
		else if ((*buffer)[i] == '$')
		{
			expand_env_no_quotes(buffer, &i, memptr);
			i--;
		}
		i++;
	}
}

void	clean_heredoc_child(t_memptr memptr,
			t_command_table **command_table)
{
	t_env		*envv;

	(void)command_table;
	envv = get_envv();
	free_envv(envv);
	clean_memory_heredoc(&memptr);
	if (*memptr.envp)
		ft_free_tabs((void **)memptr.envp);
}
