/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/05 14:02:36 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	define_quote_flag(char c, int *pos, char *quote_flag)
{
	if (*quote_flag == '\0' && (c == SQUOTE || c == DQUOTE))
		*quote_flag = c;
	else if (ft_isquote(*quote_flag) && (c == *quote_flag))
		*quote_flag = '\0';
	(void)(*pos);
}

void	expand_double_vector(char **vector, t_memptr memptr)
{
	int		vector_index;
	int		i;
	char	quote_flag;

	vector_index = 0;
	while (vector[vector_index])
	{
		quote_flag = '\0';
		i = 0;
		while ((vector[vector_index])[i])
		{
			define_quote_flag(vector[vector_index][i], &i, &quote_flag);
			if (quote_flag == '\0')
				normal_expansion(&vector[vector_index], &i,
					&quote_flag, memptr);
			else if (quote_flag == SQUOTE)
				squote_expansion(&vector[vector_index], &i,
					&quote_flag, memptr);
			else if (quote_flag == DQUOTE)
				dquote_expansion(&vector[vector_index], &i,
					&quote_flag, memptr);
		}
		vector_index++;
	}
}

void	expand_command_table(t_command_table **command_table, t_memptr memptr)
{
	t_command_table	*current;

	current = *command_table;
	while (current)
	{
		expand_double_vector(current->cmd, memptr);
		expand_double_vector(current->full_input, memptr);
		expand_double_vector(current->full_output, memptr);
		current = current->next;
	}
}
