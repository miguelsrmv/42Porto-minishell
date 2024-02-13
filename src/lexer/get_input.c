/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:41:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/13 16:44:44 by mde-sa--         ###   ########.fr       */
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
	char	*added_input;
	char	*input_nl;
	char	*temp;

	added_input = readline("> ");
	input_nl = ft_strjoin(*input, "\n");
	if (!input_nl)
	{
		free(*input);
		free(added_input);
		exit_error(MALLOC_ERROR, memptr, NULL);
	}
	temp = *input;
	*input = ft_strjoin(input_nl, added_input);
	free(temp);
	free(input_nl);
	free(added_input);
	if (!(*input))
		exit_error(MALLOC_ERROR, memptr, NULL);
}

char	*get_input(char *prompt, t_memptr memptr)
{
	char							*input;

	input = readline(prompt);
	if (!input)
		exit_error(EOF_ERROR, memptr, NULL);
	if (iscommandempty(input, memptr))
		return (NULL);
	if (check_in_quote(input) != OUT_QUOTE)
	{
		non_exit_error(QUOTE_ERROR, memptr, NULL);
		return (NULL);
	}
	else if (input[0] == '|')
	{
		non_exit_error(SYNTAX_ERROR, memptr, NULL);
		return (NULL);
	}
	trim_left_whitespace(&input, memptr);
	while (check_in_pipe(input))
		update_input(&input, memptr);
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
