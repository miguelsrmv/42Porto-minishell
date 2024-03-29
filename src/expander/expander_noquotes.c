/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_noquotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:30:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 16:23:47 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_expansion(char **string, int *pos, char *quote_flag,
			t_memptr memptr)
{
	while ((*string)[*pos] && (*string)[*pos] != *quote_flag)
	{
		if ((*string)[*pos] == '$' && !(*string)[(*pos) + 1])
			(*pos)++;
		else if ((*string)[*pos] == '$' && ((*string)[(*pos) + 1])
			&& (*string)[(*pos) + 1] == '?')
			exit_value_expand(string, pos, memptr);
		else if ((*string)[*pos] == '$' && ((*string)[(*pos) + 1]) == SQUOTE)
			ansi_quoting(string, pos, memptr);
		else if ((*string)[*pos] == '$' && ((*string)[(*pos) + 1]) == DQUOTE)
			localization(string, pos, memptr);
		else if ((*string)[*pos] == '$' && ((*string)[(*pos) + 1]) != '=')
		{
			expand_env_no_quotes(string, pos, memptr);
			(*memptr.command_table)->command_type = NO_NULL_COMMANDTYPE;
			break ;
		}
		else if (ft_isquote((*string)[*pos]))
			break ;
		else
			(*pos)++;
	}
}

void	exit_value_expand(char **string, int *start, t_memptr memptr)
{
	char	*exit_value_str;

	memptr.return_value = g_status_flag;
	exit_value_str = ft_itoa(memptr.return_value);
	if (!exit_value_str)
		exit_error(MALLOC_ERROR, memptr, NULL);
	if (concatenate(string, exit_value_str, start, (*start) + 2) == 1)
		exit_error(MALLOC_ERROR, memptr, NULL);
	(*start) = (*start) + ft_strlen(exit_value_str);
	free(exit_value_str);
}

void	ansi_quoting(char **string, int *start, t_memptr memptr)
{
	char	*substring;
	int		end;

	end = (*start) + 2;
	while ((*string)[end] != ((*string)[*start + 1]))
		end++;
	substring = ft_substr((*string), (*start) + 2, end - (*start) - 2);
	if (!substring)
		exit_error(MALLOC_ERROR, memptr, NULL);
	if (concatenate(string, substring, start, end + 1) == 1)
		exit_error(MALLOC_ERROR, memptr, NULL);
	(*start) = (*start) + ft_strlen(substring);
	free(substring);
}

void	expand_env_no_quotes(char **string, int *start, t_memptr memptr)
{
	char	*substring;
	char	*expanded;
	int		end;

	expanded = NULL;
	end = (*start) + 1;
	if (ft_isdigit((*string)[end]))
		end++;
	else
	{
		while (is_valid_env_char((*string)[end]))
			end++;
	}
	substring = ft_substr((*string), (*start) + 1, end - (*start) - 1);
	if (!substring)
		exit_error(MALLOC_ERROR, memptr, NULL);
	expanded = get_echo_var(substring, memptr);
	if (!expanded)
		expanded = "";
	free(substring);
	if (concatenate(string, expanded, start, end) == 1)
		exit_error(MALLOC_ERROR, memptr, NULL);
	(*start) = (*start) + ft_strlen(expanded);
}

void	localization(char **string, int *start, t_memptr memptr)
{
	char	*placeholder;

	placeholder = "";
	if (concatenate(string, placeholder, start, (*start) + 1) == 1)
		exit_error(MALLOC_ERROR, memptr, NULL);
}
