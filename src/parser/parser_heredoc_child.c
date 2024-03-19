/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:56:11 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 15:54:11 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(char *delimiter, int *pipe_fd,
			enum e_QuoteType quote_status, t_memptr memptr)
{
	char		*input;
	size_t		*input_size;
	t_env		*envv;

	input_size = (size_t *)malloc(sizeof(size_t));
	while (TRUE)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, delimiter))
			break ;
		expand_buffer(&input, memptr, quote_status);
		*input_size = ft_strlen(input);
		write(pipe_fd[1], input_size, sizeof(size_t));
		write(pipe_fd[1], input, ft_strlen(input));
		write(pipe_fd[1], "\n", 1);
		free(input);
	}
	close(pipe_fd[1]);
	envv = get_envv();
	free_envv(envv);
	clean_memory(memptr);
	if (*memptr.envp)
		ft_free_tabs((void **)memptr.envp);
	exit(g_status_flag);
}

 void	expand_buffer(char **buffer, t_memptr memptr, enum e_QuoteType quote_status)
{
	int	i;
	if (quote_status != OUT_QUOTE)
		return ;;
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