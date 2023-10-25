/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:41:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/22 14:04:27 by mde-sa--         ###   ########.fr       */
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

char	*get_input(char *prompt)
{
	char	*input;
	char	*added_input;
	char	*temp;

	input = readline(prompt);
	while (check_in_quote(input) != OUT_QUOTE)
	{
		added_input = readline(">");
		temp = input;
		input = ft_strjoin(input, added_input);
		free(temp);
		free(added_input);
	}
	input = check_valid_input(input);
	return (input);
}