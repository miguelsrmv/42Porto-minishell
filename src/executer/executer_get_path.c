/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:48:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/16 14:29:36 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_result_from_path_list(char **path_list, char **result,
			t_memptr memptr)
{
	int		i;
	char	*temp;

	i = 0;
	result[0] = ft_strdup("");
	if (!result[0])
		exit_error(MALLOC_ERROR, memptr);
	temp = getcwd(NULL, 0);
	result[1] = ft_strjoin(temp, "/");
	free(temp);
	if (!result[1])
		exit_error(MALLOC_ERROR, memptr);
	i = 0;
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		if (!temp)
			exit_error(MALLOC_ERROR, memptr);
		result[i + 2] = ft_strdup(temp);
		free(temp);
		if (!result[i + 2])
			exit_error(MALLOC_ERROR, memptr);
		i++;
	}
	result[i + 2] = NULL;
}

char	**get_path_list(t_memptr *memptr)
{
	char	**path_list;
	int		i;
	char	**result;

	path_list = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path_list[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 3));
	if (!result)
		exit_error(MALLOC_ERROR, *memptr);
	fill_in_result_from_path_list(path_list, result, *memptr);
	ft_free_tabs((void **)path_list);
	memptr->path_list = result;
	return (result);
}
