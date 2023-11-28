/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:41:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/28 14:50:26 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in_quote(char *input)
{
	int	i;
	int	quote_status;

	i = 0;
	quote_status = OUT_QUOTE;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote_status = input[i];
			i++;
			while (input[i] != quote_status && input[i])
				i++;
			if (input[i] == quote_status)
			{
				quote_status = OUT_QUOTE;
				i++;
			}
		}
		else
			i++;
	}
	return (quote_status);
}

/// Check if only valid characters are being used. Add in error exit here.
char	*check_valid_input(char *input)
{
	return (input);
}

void	trim_left_whitespace(char **input, t_memptr memptr)
{
	int		i;
	char	*temp;

	i = 0;
	temp = *input;
	while ((*input)[i] == ' ')
		i++;
	*input = ft_strdup(&(*input)[i]);
	if (!(*input))
		exit_error(MALLOC_ERROR, memptr);
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
		exit_error(MALLOC_ERROR, memptr);
	}
	temp = *input;
	*input = ft_strjoin(input_nl, added_input);
	free(temp);
	free(input_nl);
	free(added_input);
	if (!(*input))
		exit_error(MALLOC_ERROR, memptr);
}

char	*get_input(char *prompt, t_memptr memptr)
{
	char	*input;

	input = readline(prompt);
	trim_left_whitespace(&input, memptr);
	while (check_in_quote(input) != OUT_QUOTE)
		update_input(&input, memptr);
	rl_replace_line(input, 0);
	rl_redisplay();
	input = check_valid_input(input);
	if (input && ft_strlen(input))
		add_history(input);
	return (input);
}
