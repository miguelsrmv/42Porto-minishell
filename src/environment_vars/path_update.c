/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:23:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/23 11:26:51 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_memptr *memptr)
{
	char	*my_oldpwd;

	my_oldpwd = getenv("OLDPWD");
	if (my_oldpwd == NULL)
		exit_error(MALLOC_ERROR, *memptr, NULL); // TODO: Check
	memptr->my_oldpwd = my_oldpwd;
}

void	update_pwd(t_memptr *memptr)
{
	char	*my_pwd;

	my_pwd = getenv("PWD");
	if (my_pwd == NULL)
		exit_error(MALLOC_ERROR, *memptr, NULL); // TODO: Check
	memptr->my_pwd = my_pwd;
}

void	update_path(t_memptr *memptr)
{
	char	*path;

	path = get_env_value(memptr->envp, "PATH", memptr);
	if (path == NULL)
		exit_error(MALLOC_ERROR, *memptr, NULL); // TODO: Check
	memptr->path_list = ft_split(path, ':');
	if (!(memptr->path_list))
		exit_error(MALLOC_ERROR, *memptr, NULL);
}

void	update_environment(t_memptr *memptr)
{
	update_oldpwd(memptr);
	update_pwd(memptr);
	update_path(memptr);
}
