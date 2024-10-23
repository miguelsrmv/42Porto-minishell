/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_minus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:17:43 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/23 12:13:37 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cd_minus_envs(char *new_dir, char *old_dir, t_memptr *memptr)
{
	int		pwd_position;
	char	*curr_dir;

	pwd_position = find_env_var(memptr->envp, "PWD");
	if (pwd_position >= 0)
		update_pwd_location(new_dir, memptr);
	update_oldpwd_location(old_dir, memptr);
	curr_dir = getcwd(NULL, 0);
	if (!old_dir)
	{
		g_status_flag = 1;
		perror("Error");
		return ;
	}
	printf("%s\n", curr_dir);
	free(curr_dir);
	free(old_dir);
}
