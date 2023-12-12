/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/12 17:16:54 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (!ft_printf("%s\n", cwd))
	{
		ft_free_str(&cwd);
		perror("\nError: printf failed");
		return (EXIT_FAILURE);
	}
	ft_free_str(&cwd);
	return (EXIT_SUCCESS);
}
