/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeout_nullstrings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:57:21 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/18 13:58:44 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	takeout_nullstrings(t_command_table	*current, char **tab, t_memptr memptr)
{
    int 	nonEmptyCount;
    int 	i;
	char **	newTab;

	nonEmptyCount = 0;
    i = 0;
    while (tab[i] != NULL)
	{
        if (ft_strcmp(tab[i], "") != 0 && ft_strcmp(tab[i], "''") != 0)
            nonEmptyCount++;
        i++;
    }
    newTab = (char **)malloc((nonEmptyCount + 1) * sizeof(char *));
    if (newTab == NULL)
		exit_error(MALLOC_ERROR, memptr, NULL);
	copy_non_null_strings(newTab, tab, memptr);
	current->cmd = newTab;
}

void	copy_non_null_strings(char **newTab, char **tab, t_memptr memptr)
{
	int	j;
	int	i;
	
	j = 0;
    i = 0;
    while (tab[i] != NULL)
	{
        if (ft_strcmp(tab[i], "") != 0 && ft_strcmp(tab[i], "''") != 0)
		{
            newTab[j] = ft_strdup(tab[i]);
            if (newTab[j] == NULL)
			{
				ft_free_tabs((void **)newTab);
                exit_error(MALLOC_ERROR, memptr, NULL);
            }
            j++;
        }
        i++;
    }
    newTab[j] = NULL;
    ft_free_tabs((void **)tab);
}
