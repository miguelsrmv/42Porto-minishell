/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:23:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/26 20:10:02 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_path(t_memptr *memptr)
{
	char	*path;

	path = get_env_value(memptr->envp, "PATH", memptr);
	if (!path)
		return ;
	memptr->path_list = ft_split(path, ':');
	if (!(memptr->path_list))
		exit_error(MALLOC_ERROR, *memptr, NULL);
}
