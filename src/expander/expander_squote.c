/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_squote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:30:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 11:27:46 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	squote_expansion(char **string, int *pos, char *quote_flag,
			t_memptr memptr)
{
	take_out_outer_squotes(string, pos, quote_flag, memptr);
}

void	take_out_outer_squotes(char **string, int *start, char *quote_flag,
			t_memptr memptr)
{
	char	*unquoted_char;
	int		end;

	end = (*start) + 1;
	while ((*string)[end] != *quote_flag)
		end++;
	unquoted_char = ft_substr((*string), (*start) + 1, end - (*start) - 1);
	if (!unquoted_char)
		exit_error(MALLOC_ERROR, memptr, NULL);
	if (concatenate(string, unquoted_char, start, end + 1) == 1)
		exit_error(MALLOC_ERROR, memptr, NULL);
	(*start) = (*start) + ft_strlen(unquoted_char);
	free(unquoted_char);
	(*quote_flag) = '\0';
}
