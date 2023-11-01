/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/01 15:22:58 by mde-sa--         ###   ########.fr       */
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
	int		vector_i;
	int		i;
	char	quote_status;

	vector_i = 0;
	while (vector[vector_i])
	{
		i = 0;
		quote_status = '\0';
		if ((vector[vector_i])[i] == squote)
		{
			quote_status = vector[vector_i][i];
			i++;
		}
		while ((vector[vector_i])[i])
		{
			if (quote_status == squote)
			{
				while (vector[vector_i][i] != quote_status && vector[vector_i][i])
					i++;
				quote_status = '\0';
				i++;
			}
			else
			{
				while (quote_status != squote && (vector[vector_i][i]))
				{
					if (vector[vector_i][i] == '$')
						vector[vector_i] = expand_env(vector[vector_i], i);
					else if (vector[vector_i][i] == squote)
						quote_status = vector[vector_i][i];
					i++;
				}
			}
		}
		vector_i++;
	}
}

void	contract_double_vector(char **vector)
{
	int		vector_i;
	int		i;
	int		j;
	char	quote_status;
	char	*result;
	char	*temp;

	vector_i = 0;
	while (vector[vector_i])
	{
		result = (char *)malloc(sizeof(vector[vector_i]));
		if (!result)
			return ;
		quote_status = '\0';
		i = 0;
		j = 0;
		while ((vector[vector_i])[i])
		{
			if (ft_isquote((vector[vector_i])[i]))
			{
				quote_status = vector[vector_i][i];
				i++;
			}
			if (quote_status)
			{
				while (vector[vector_i][i] != quote_status && vector[vector_i][i])
					result[j++] = vector[vector_i][i++];
				quote_status = '\0';
				i++;
			}
			else if (!quote_status)
			{
				while (!quote_status && (vector[vector_i][i]))
				{
					result[j++] = vector[vector_i][i++];
					if (ft_isquote(vector[vector_i][i]))
						quote_status = vector[vector_i][i];
				}
			}
		}
		j++;
		result[j] = '\0';
		temp = vector[vector_i];
		vector[vector_i] = result;
		free(temp);
		vector_i++;
	}
}

void	expand_command_table(t_command_table **command_table)
{
	t_command_table	*current;

	current = *command_table;
	while (current)
	{
		expand_double_vector(current->cmd);
		contract_double_vector(current->cmd);
		expand_double_vector(current->full_input);
		contract_double_vector(current->full_input);
		expand_double_vector(current->full_output);
		contract_double_vector(current->full_output);
		current = current->next;
	}
}
