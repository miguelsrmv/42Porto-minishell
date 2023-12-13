/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:41:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/13 14:54:36 by mde-sa--         ###   ########.fr       */
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
	char							*input;

	input = readline(prompt);
	if (!input)
		exit_error(EOF_ERROR, memptr);
	trim_left_whitespace(&input, memptr);
	if (check_in_quote(input) != OUT_QUOTE)
		exit_error(QUOTE_ERROR, memptr);
	if (input[0] == '|')
		exit_error(SYNTAX_ERROR, memptr);
	while (check_in_pipe(input))
		update_input(&input, memptr);
	rl_replace_line(input, 0);
	rl_redisplay();
	input = check_valid_input(input); // retirar ?? Checkar caractéres inválidos ? 
	if (input && ft_strlen(input))
		add_history(input);
	return (input);
}
