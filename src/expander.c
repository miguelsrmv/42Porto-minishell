/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/24 18:26:08 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid_env_char(char c)
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

char	*expand_env(char *string)
{
	char	*left;
	char	*env;
	char	*right;
	int		i;

	i = 0;
	while (string && string[i])
	{
		if (string[i] == '$')
		{
			left = ft_substr(string, 0, i);
			i++;
			while (is_valid_env_char(string[i]) && string[i])
				i++;
			env = ft_substr(string, ft_strlen(left) + 1,
					i - ft_strlen(left) - 1);
			right = ft_substr(string, i, ft_strlen(string) - i);
			string = concatenate_env_substrings(left, env, right, string);
			i = -1;
		}
		i++;
	}
	return (string);
}

void	expand_double_vector(t_command_table **command_table, char **vector)
{
	int				i;
	char			*temp;

	i = 0;
	while (vector[i])
	{
		if (ft_strchr(vector[i], '$') && vector[i][0] != '\'')
		{
			if (vector[i][0] == '\"')
			{
				temp = vector[i];
				vector[i] = ft_substr(vector[i], 1, ft_strlen(vector[i]) - 2);
				free(temp);
			}
			vector[i] = expand_env(vector[i]);
		}
		else if (vector[i][0] == '\'' || vector[i][0] == '\"')
		{
			temp = vector[i];
			vector[i] = ft_substr(vector[i], 1, ft_strlen(vector[i]) - 2);
			free(temp);
		}
		i++;
	}
}

void	expand_command_table(t_command_table **command_table)
{
	t_command_table	*current;

	current = *command_table;
	while (current)
	{
		expand_double_vector(command_table, (*command_table)->cmd);
		expand_double_vector(command_table, (*command_table)->full_input);
		expand_double_vector(command_table, (*command_table)->full_output);
		current = current->next;
	}
}
