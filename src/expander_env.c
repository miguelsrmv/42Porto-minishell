/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/15 11:05:58 by mde-sa--         ###   ########.fr       */
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
	char	*expanded;
	char	*result;
	char	*temp;

	if (ft_strchr(env, squote) || ft_strchr(env, dquote))
	{
		expanded = take_out_quotes(env);
		result = ft_strjoin(left, expanded);
		free (expanded);
	}
	else
		result = ft_strjoin(left, getenv(env));
	temp = result;
	result = ft_strjoin(result, right);
	free(temp);
	free(string);
	free(left);
	free(env);
	free(right);
	if (result == NULL)
		return (ft_strdup("\0"));
	return (result);
}

// Além da expansão, fazer concatenate de left + esta substring + right e atualizar *start!!!....
void	expand(char **string, int *start, char quote_flag)
{
	if (!(*string)[(*start) + 1])
		expand_to_dollar_sign(string, start);
	else if (!quote_flag && (*string)[(*start) + 1] != squote)
		expand_env(string, start);
	else if (!quote_flag && (*string)[(*start) + 1] == squote)
		take_out_after_quotes(string, start);
	else if (quote_flag && (*string)[(*start) + 1] != squote)
		expand_env(string, start);
	else if (quote_flag && (*string)[(*start) + 1] == squote)
		take_out_quote_flag(string, start);
}

/*
char	*expand_env(char *string, int start)
{
	char	*left;
	char	*env;
	char	*right;
	int		i;

	if (!ft_strchr(string, squote) && !ft_strchr(string, dquote))
	{
		i = start;
		left = ft_substr(string, 0, i);
		i++;
		while (is_valid_env_char(string[i]) && string[i])
			i++;
		env = ft_substr(string, ft_strlen(left) + 1,
				i - ft_strlen(left) - 1);
		right = ft_substr(string, i, ft_strlen(string) - i);
		string = concatenate_env_substrings(left, env, right, string);
	}
	else
	{
		env = ft_substr(string, 1, ft_strlen(string) - 1);
		string = env;
		free (env);
	}
	return (string);
}
*/

void	expand_double_vector(char **vector)
{
	int		vector_index;
	int		i;
	char	quote_flag;

	vector_index = 0;
	while (vector[vector_index])
	{
		i = 0;
		quote_flag = '\0';
		while ((vector[vector_index])[i])
		{
			if (ft_isquote((vector[vector_index])[i]) && quote_flag == '\0')
				quote_flag = vector[vector_index][i++];
			while (quote_flag == squote && vector[vector_index][i] != squote
					&& vector[vector_index][i])
				i++;
			if (ft_isquote((vector[vector_index])[i])
				&& vector[vector_index][i] == quote_flag)
				quote_flag = '\0';
			else if (vector[vector_index][i] == '$')
				expand_env(&vector[vector_index], &i, quote_flag);
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
/*		contract_double_vector(current->cmd);
		contract_double_vector(current->full_input);
		contract_double_vector(current->full_output);
		current = current->next;*/
	}
}
