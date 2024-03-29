/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:41:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 15:41:05 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_left_whitespace(char **input, t_memptr memptr)
{
	int		i;
	char	*temp;

	i = 0;
	temp = *input;
	while (ft_isspace((*input)[i]))
		i++;
	*input = ft_strdup(&(*input)[i]);
	if (!(*input))
		exit_error(MALLOC_ERROR, memptr, NULL);
	free(temp);
}

void	update_input(char **input, t_memptr memptr)
{
	int		pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		exit_error(FORK_ERROR, memptr, NULL);
	else if (pid == 0)
	{
		clean_input(*input, memptr);
		set_signal_inputs_child();
		close(pipe_fd[0]);
		pipe_child(pipe_fd);
	}
	else
	{
		set_signal_inputs_parent();
		close(pipe_fd[1]);
		pipe_parent(input, pipe_fd, memptr);
		set_signal();
	}
}

char	*get_input(char *prompt, t_memptr memptr)
{
	char							*input;

	input = readline(prompt);
	if (!input)
		exit_error(EMPTY_INPUT_ERROR, memptr, NULL);
	trim_left_whitespace(&input, memptr);
	if (iscommandempty(input, memptr))
	{
		free(input);
		return (NULL);
	}
	else if (input[0] == '|')
	{
		non_exit_error(SYNTAX_ERROR, memptr, NULL);
		free(input);
		return (NULL);
	}
	while (check_in_pipe(input))
	{
		update_input(&input, memptr);
		if (!input)
			return (NULL);
	}
	return (get_input_2(input, memptr));
}

char	*get_input_2(char *input, t_memptr memptr)
{
	if (check_in_quote(input) != OUT_QUOTE)
	{
		non_exit_error(QUOTE_ERROR, memptr, NULL);
		free(input);
		return (NULL);
	}
	rl_replace_line(input, 0);
	rl_redisplay();
	if (input && ft_strlen(input))
		add_history(input);
	return (input);
}

bool	iscommandempty(const char *cmd, t_memptr memptr)
{
	bool	insinqlequote;
	bool	indoublequote;
	int		i;

	insinqlequote = false;
	indoublequote = false;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' && !indoublequote)
			insinqlequote = !insinqlequote;
		else if (cmd[i] == '\"' && !insinqlequote)
			indoublequote = !indoublequote;
		else if (!ft_isspace((unsigned char)cmd[i]))
			return (false);
		i++;
	}
	if (ft_strlen(cmd))
		non_exit_error(COMMAND_ERROR, memptr, (char *)cmd);
	return (true);
}
