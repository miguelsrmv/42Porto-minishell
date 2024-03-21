/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_nullstrings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:28:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/21 18:17:22 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_nullstrings(char **command, t_memptr memptr)
{
	int		null_count;
	int		tab_len;
	char	**trimmed_command;
	int		i;

	tab_len = ft_tablen((void **)command);
	null_count = 0;
	i = 0;
	while (command[i])
	{
		if (ft_strlen(command[i++]) == 0)
			null_count++;
	}
	trimmed_command = (char **)malloc(sizeof(char *)
			* (tab_len - null_count + 1));
	if (!trimmed_command)
		exit_error(MALLOC_ERROR, memptr, NULL);
	trimmed_command = copy_nonnullstrings(command, trimmed_command, memptr);
	return (trimmed_command);
}

char	**copy_nonnullstrings(char **command,
			char **trimmed_command, t_memptr memptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (ft_strlen(command[i]) != 0)
		{
			trimmed_command[j] = ft_strdup(command[i]);
			if (!trimmed_command[j])
			{
				ft_free_tabs((void **)trimmed_command);
				exit_error(MALLOC_ERROR, memptr, NULL);
			}
			j++;
		}
		i++;
	}
	trimmed_command[j] = NULL;
	ft_free_tabs((void **)command);
	return (trimmed_command);
}
