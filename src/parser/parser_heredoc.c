/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:02:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 15:44:32 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredocs(t_command_table **command_table, t_memptr memptr)
{
	int					i;
	char				*delimiter;
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
			analyze_delimiter(&delimiter, (*command_table)->full_input[i + 1],
				&quote_status, memptr);
			create_heredoc_buffer(delimiter,
				&(*command_table)->heredoc_buffer, quote_status, memptr);
			free(delimiter);
		}
		i = i + 2;
	}
	if ((*command_table)->heredoc_buffer)
		create_heredoc(command_table, (*command_table)->heredoc_buffer, memptr);
}

// Define se delimitador está ou não sob aspas, e retira as aspas do mesmo
void	analyze_delimiter(char **unquoted_delimiter, char *delimiter,
			enum e_QuoteType *quote_status, t_memptr memptr)
{
	int	i;

	*quote_status = OUT_QUOTE;
	i = 0;
	if (*delimiter == SQUOTE)
		*quote_status = IN_QUOTE;
	else if (*delimiter == DQUOTE)
		*quote_status = IN_DQUOTE;
	if ((*quote_status) != OUT_QUOTE)
		i++;
	*unquoted_delimiter = ft_strndup(delimiter + i,
			ft_strlen(delimiter) - 2 * i);
	if (!*unquoted_delimiter)
		exit_error(MALLOC_ERROR, memptr, NULL);
}

void	create_heredoc_buffer(char *delimiter, char **buffer,
			enum e_QuoteType quote_status, t_memptr memptr)
{
	int		bytes_read;
	char	input[1001];
	char	*temp;

	*buffer = ft_calloc(1, sizeof(char));
	if (!(*buffer))
		exit_error(MALLOC_ERROR, memptr, NULL);
	while (TRUE)
	{
		ft_printf("> ");
		bytes_read = read(STDIN_FILENO, input, 1000);
		if (bytes_read == -1 || bytes_read == 0)
			break ;
		input[bytes_read] = '\0';
		if (!ft_strcmp_input(input, delimiter))
			break ;
		temp = ft_strjoin(*buffer, input);
		if (!temp)
			exit_error(MALLOC_ERROR, memptr, NULL);
		free(*buffer);
		*buffer = temp;
	}
	if (quote_status == OUT_QUOTE)
		expand_buffer(buffer, memptr);
}

// Expansão de heredoc caso delimitador não esteja com aspas
void	expand_buffer(char **buffer, t_memptr memptr)
{
	int	i;

	i = 0;
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == '$')
		{
			expand_env_no_quotes(buffer, &i, memptr);
			i--;
		}
		i++;
	}
}

// Versão antiga do expand_buffer
/* void	expand_buffer(char **buffer, t_memptr memptr)
{
	int					i;
	enum e_QuoteType	quote_flag;

	i = 0;
	quote_flag = OUT_QUOTE;
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == SQUOTE)
			quote_flag = IN_QUOTE;
		while (((*buffer)[i]) && quote_flag == IN_QUOTE
			&& ((*buffer)[i]) != SQUOTE)
		{
			if ((*buffer)[i++] == SQUOTE)
				quote_flag = OUT_QUOTE;
		}
		if ((*buffer)[i] == '$')
		{
			expand_env_no_quotes(buffer, &i, memptr);
			i--;
		}
		i++;
	}
} */

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
