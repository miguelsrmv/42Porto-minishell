/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:12:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/02 22:49:38 by mde-sa--         ###   ########.fr       */
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

int	check_in_pipe(char *input)
{
	int	i;
	int	pipe_status;

	i = 0;
	pipe_status = OUT_PIPE;
	while (input[i])
	{
		if ((input[i]) != '|')
		{
			pipe_status = OUT_PIPE;
			i++;
		}
		else if (input[i] == '|')
		{
			pipe_status = IN_PIPE;
			i++;
		}
		while (ft_isspace(input[i]))
			i++;
	}
	return (pipe_status);
}

char	*check_valid_input(char *input)
{
	return (input);
}
