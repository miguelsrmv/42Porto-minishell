/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:48:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/28 18:09:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_result_from_path_list(char **path_list, char **result,
			t_memptr memptr)
{
	int		i;
	char	*temp;

	i = 0;
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		if (!temp)
			exit_error(MALLOC_ERROR, memptr, NULL);
		result[i] = ft_strdup(temp);
		free(temp);
		if (!result[i])
			exit_error(MALLOC_ERROR, memptr, NULL);
		i++;
	}
	result[i] = NULL;
}

char	**get_path_list(t_memptr *memptr)
{
	char	**path_list;
	int		i;
	char	**result;

	path_list = memptr->path_list;
	i = 0;
	while (path_list[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 3));
	if (!result)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	fill_in_result_from_path_list(path_list, result, *memptr);
	ft_free_tabs((void **)path_list);
	memptr->path_list = result;
	return (result);
}
