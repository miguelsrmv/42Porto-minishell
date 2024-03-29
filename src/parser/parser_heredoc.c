/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:02:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 14:46:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredocs(t_command_table **command_table, t_memptr memptr)
{
	int					i;
	char				delimiter[1024];
	enum e_QuoteType	quote_status;

	i = 0;
	while ((*command_table)->full_input[i])
	{
		if (ft_strlen((*command_table)->full_input[i]) == 2
			&& !ft_strncmp("<<", (*command_table)->full_input[i], 2))
		{
			if ((*command_table)->heredoc_buffer)
			{
				free((*command_table)->heredoc_buffer);
				(*command_table)->heredoc_buffer = NULL;
			}
			analyze_delimiter(delimiter, (*command_table)->full_input[i + 1],
				&quote_status, memptr);
			create_heredoc_buffer(delimiter, command_table, quote_status,
				memptr);
		}
		i = i + 2;
		if (g_status_flag == 8)
			break ;
	}
}

void	analyze_delimiter(char *unquoted_delimiter, char *delimiter,
			enum e_QuoteType *quote_status, t_memptr memptr)
{
	int		i;
	char	*trimmed_delimiter;

	trimmed_delimiter = NULL;
	*quote_status = OUT_QUOTE;
	i = 0;
	if (*delimiter == SQUOTE)
		*quote_status = IN_QUOTE;
	else if (*delimiter == DQUOTE)
		*quote_status = IN_DQUOTE;
	if ((*quote_status) != OUT_QUOTE)
		i++;
	trimmed_delimiter = ft_strndup(delimiter + i,
			ft_strlen(delimiter) - 2 * i);
	if (!trimmed_delimiter)
		exit_error(MALLOC_ERROR, memptr, NULL);
	ft_memcpy(unquoted_delimiter, trimmed_delimiter,
		ft_strlen(trimmed_delimiter));
	unquoted_delimiter[ft_strlen(trimmed_delimiter)] = '\0';
	free(trimmed_delimiter);
}

void	create_heredoc_buffer(char *delimiter, t_command_table **command_table,
			enum e_QuoteType quote_status, t_memptr memptr)
{
	int					pid;
	int					pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		exit_error(FORK_ERROR, memptr, NULL);
	else if (pid == 0)
	{
		set_signal_inputs_child();
		close(pipe_fd[0]);
		clean_heredoc_child(memptr, command_table);
		heredoc_child(delimiter, pipe_fd);
		exit(g_status_flag);
	}
	else
	{
		set_signal_inputs_parent();
		close(pipe_fd[1]);
		heredoc_parent(&((*command_table)->heredoc_buffer), pipe_fd,
			memptr, quote_status);
		set_signal();
	}
}

void	create_heredoc(t_command_table **command_table,
			char *buffer, t_memptr memptr)
{
	char	*name;
	int		i;
	int		fd;

	i = 0;
	while (TRUE)
	{
		name = ft_itoa(i);
		if (access(name, F_OK) != 0)
			break ;
		free(name);
		i++;
	}
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(OPEN_ERROR, memptr, name);
	if (write(fd, buffer, ft_strlen(buffer)) == -1)
		exit_error(WRITE_ERROR, memptr, NULL);
	if (close(fd) == -1)
		exit_error(CLOSE_ERROR, memptr, NULL);
	free(buffer);
	(*command_table)->heredoc_buffer = name;
}
