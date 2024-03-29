/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:23:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 11:32:07 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_path(char **envp, t_memptr *memptr)
{
	char	*path;
	char	**path_list;

	path = return_path_from_envp(envp, memptr);
	if (!path)
		return ;
	path_list = ft_split(path, ':');
	if (!path_list)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	free(path);
	memptr->path_list = path_list;
}

char	*return_path_from_envp(char **envp, t_memptr *memptr)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_strdup(&envp[i][5]);
			if (!path)
				exit_error(MALLOC_ERROR, *memptr, NULL);
			break ;
		}
		i++;
	}
	return (path);
}
