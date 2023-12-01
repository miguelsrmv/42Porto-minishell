/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_noquotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:30:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/01 16:01:36 by bmota-si         ###   ########.fr       */
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
		else if ((*string)[*pos] == '$' && (*string)[(*pos) + 1]
			&& (*string)[(*pos) + 1] == '$')
			expand_to_pid(string, pos, memptr);
		else if ((*string)[*pos] == '$' && ((*string)[(*pos) + 1]) == SQUOTE)
			ansi_quoting(string, pos, memptr);
		else if ((*string)[*pos] == '$' && ((*string)[(*pos) + 1]) == DQUOTE)
			localization(string, pos, memptr);
		else if ((*string)[*pos] == '$')
		{
			expand_env_no_quotes(string, pos, memptr);
			break ;
		}
		else if (ft_isquote((*string)[*pos]))
			break ;
		else
			(*pos)++;
	}
}

void	expand_to_pid(char **string, int *start, t_memptr memptr)
{
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		exit_error(MALLOC_ERROR, memptr);
	if (concatenate(string, pid_str, start, (*start) + 2) == 1)
		exit_error(MALLOC_ERROR, memptr);
	(*start) = (*start) + ft_strlen(pid_str);
	free(pid_str);
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
		exit_error(MALLOC_ERROR, memptr);
	if (concatenate(string, substring, start, end + 1) == 1)
		exit_error(MALLOC_ERROR, memptr);
	(*start) = (*start) + ft_strlen(substring);
	free(substring);
}

void	expand_env_no_quotes(char **string, int *start, t_memptr memptr)
{
	char	*substring;
	char	*expanded;
	//t_env	*envv;
	int		end;

	end = (*start) + 1;
	while (is_valid_env_char ((*string)[end]))
		end++;
	substring = ft_substr((*string), (*start) + 1, end - (*start) - 1);
	if (!substring)
		exit_error(MALLOC_ERROR, memptr);
	//expanded = getenv(substring);
	expanded = get_echo_var(substring);
	if (!expanded)
		expanded = "";
	free(substring);
	if (concatenate(string, expanded, start, end) == 1)
		exit_error(MALLOC_ERROR, memptr);
	(*start) = (*start) + ft_strlen(expanded);
}

void	localization(char **string, int *start, t_memptr memptr)
{
	char	*placeholder;

	placeholder = "";
	if (concatenate(string, placeholder, start, (*start) + 1) == 1)
		exit_error(MALLOC_ERROR, memptr);
}
