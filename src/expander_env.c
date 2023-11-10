/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/10 12:36:04 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*concatenate_env_substrings(char *left, char *env, char *right,
			char *string)
{
	char	*result;
	char	*temp;

	result = ft_strjoin(left, getenv(env));
	temp = result;
	result = ft_strjoin(result, right);
	free(left);
	free(right);
	free(temp);
	free(string);
	if (result == NULL)
		return (ft_strdup("\0"));
	return (result);
}

char	*expand_env(char *string, int start)
{
	char	*left;
	char	*env;
	char	*right;
	int		i;

	i = start;
	left = ft_substr(string, 0, i);
	i++;
	while (is_valid_env_char(string[i]) && string[i])
		i++;
	env = ft_substr(string, ft_strlen(left) + 1,
			i - ft_strlen(left) - 1);
	right = ft_substr(string, i, ft_strlen(string) - i);
	string = concatenate_env_substrings(left, env, right, string);
	i = -1;
	return (string);
}

void	expand_double_vector(char **vector)
{
	int		vector_index;
	int		i;
	char	quote_status;

	vector_index = 0;
	while (vector[vector_index])
	{
		i = 0;
		quote_status = '\0';
		while ((vector[vector_index])[i])
		{
			if (ft_isquote((vector[vector_index])[i]) && quote_status == '\0')
				quote_status = vector[vector_index][i++];
			while (quote_status == squote && vector[vector_index][i] != squote
					&& vector[vector_index][i])
				i++;
			if (ft_isquote((vector[vector_index])[i])
				&& vector[vector_index][i] == quote_status)
				quote_status = '\0';
			else if (vector[vector_index][i] == '$')
				vector[vector_index] = expand_env(vector[vector_index], i);
			i++;
		}
		vector_index++;
	}
}

void	expand_command_table(t_command_table **command_table)
{
	t_command_table	*current;

	current = *command_table;
	while (current)
	{
		expand_double_vector(current->cmd);
		expand_double_vector(current->full_input);
		expand_double_vector(current->full_output);
		//contract_double_vector(current->cmd);
		//contract_double_vector(current->full_input);
		//contract_double_vector(current->full_output);
		current = current->next;
	}
}

/// minishell: echo '$USER'$HOME

