/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/11 12:51:37 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **argv)
{
	char	*cwd;

	if (ft_builtin_checker(argv) != EXIT_SUCCESS)
		return (g_status_flag);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (!printf("%s\n", cwd))
	{
		ft_free_str(&cwd);
		perror("\nError: printf failed");
		return (EXIT_FAILURE);
	}
	ft_free_str(&cwd);
	return (EXIT_SUCCESS);
}
