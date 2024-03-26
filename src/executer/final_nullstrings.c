/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_nullstrings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:28:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/26 00:33:05 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**final_nullstrings(t_command_table *current, t_memptr memptr)
{
	int		final_len;
	char	**final_cmd;

	final_len = get_final_len(current->cmd_before_expansion,
			current->cmd);
	final_cmd = (char **)malloc((final_len + 1) * sizeof(char *));
	if (!final_cmd)
		exit_error(MALLOC_ERROR, memptr, NULL);
	fill_with_nonnullstrings(final_cmd,
		current->cmd_before_expansion, current->cmd, memptr);
	ft_free_tabs((void **)current->cmd);
	return (final_cmd);
}

void	fill_with_nonnullstrings(char **final_cmd,
			char **cmd_before_expansion, char **cmd, t_memptr memptr)
{
	int	i;
	int	j;
	int	tab_len;

	i = 0;
	j = 0;
	tab_len = ft_tablen((void **)cmd_before_expansion);
	while (j < tab_len && cmd[j])
	{
		if (is_string_truly_null(cmd_before_expansion[j], cmd[j]) == FALSE)
		{
			final_cmd[i] = ft_strdup(cmd[j]);
			if (!final_cmd)
			{
				ft_free_tabs((void **)final_cmd);
				exit_error(MALLOC_ERROR, memptr, NULL);
			}
			i++;
		}
		j++;
	}
	final_cmd[i] = NULL;
}

int	get_final_len(char **cmd_before_expansion, char **cmd)
{
	int	final_len;
	int	tab_len;
	int	i;

	final_len = 0;
	tab_len = ft_tablen((void **)cmd_before_expansion);
	i = 0;
	while (i < tab_len && cmd[i])
	{
		final_len++;
		if (is_string_truly_null(cmd_before_expansion[i], cmd[i]) == TRUE)
			final_len--;
		i++;
	}
	return (final_len);
}

bool	is_string_truly_null(char *string_before_expansion,
		char *string_after_expansion)
{
	if ((ft_strcmp(string_before_expansion, "")
			&& string_before_expansion[0] == '$')
		&& !ft_strcmp(string_after_expansion, ""))
		return (TRUE);
	return (FALSE);
}
