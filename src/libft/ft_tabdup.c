/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:57:57 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/07 10:23:38 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**newtab;
	char	*temp;
	int		i;

	i = 0;
	if (tab == NULL)
		return (NULL);
	while (tab[i] != NULL)
		i++;
	newtab = (char **)malloc(sizeof(char *) * (i + 1));
	if (newtab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		temp = ft_strdup(tab[i]);
		if (temp == NULL)
		{
			ft_free_tabs((void **)newtab);
			return (NULL);
		}
		newtab[i++] = temp;
	}
	newtab[i] = NULL;
	return (newtab);
}
