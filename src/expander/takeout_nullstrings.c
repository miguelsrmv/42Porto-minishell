/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeout_nullstrings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:57:21 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 10:03:30 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	takeout_nullstrings(t_command_table	*current, char **tab,
			t_memptr memptr)
{
	int		non_empty_count;
	int		i;
	char	**new_tab;

	non_empty_count = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strcmp(tab[i], "") != 0 && ft_strcmp(tab[i], "''") != 0)
			non_empty_count++;
		i++;
	}
	new_tab = (char **)malloc((non_empty_count + 1) * sizeof(char *));
	if (new_tab == NULL)
		exit_error(MALLOC_ERROR, memptr, NULL);
	copy_non_null_strings(new_tab, tab, memptr);
	current->cmd = new_tab;
}

void	copy_non_null_strings(char **new_tab, char **tab, t_memptr memptr)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strcmp(tab[i], "") != 0 && ft_strcmp(tab[i], "''") != 0)
		{
			new_tab[j] = ft_strdup(tab[i]);
			if (new_tab[j] == NULL)
			{
				ft_free_tabs((void **)new_tab);
				exit_error(MALLOC_ERROR, memptr, NULL);
			}
			j++;
		}
		i++;
	}
	new_tab[j] = NULL;
	ft_free_tabs((void **)tab);
}
