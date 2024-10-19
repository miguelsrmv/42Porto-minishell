/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:34:41 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/17 21:50:12 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **argv)
{
	char	*cwd;

	if (builtin_argument_checker(argv) != EXIT_SUCCESS)
		return (g_status_flag);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	ft_free_str(&cwd);
	return (EXIT_SUCCESS);
}
