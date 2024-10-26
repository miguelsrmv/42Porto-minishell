/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:23:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/26 22:09:56 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(char **envp)
{
	int	n;
	int	swapped;
	int	i;

	n = 0;
	while (envp[n] != NULL)
		n++;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < n - 1)
		{
			if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			{
				swap(&envp[i], &envp[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}
