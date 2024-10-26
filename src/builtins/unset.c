/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:42 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/26 19:51:29 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char **argv, char **envp, t_command_table *current, t_memptr *memptr)
{
	int	i;

	(void)current;
	(void)envp;
	if (!argv[1])
		return (EXIT_SUCCESS);
	if (builtin_argument_checker(argv) == EXIT_FAILURE)
		return (g_status_flag);
	i = 1;
	while (argv[i])
	{
		if (!ft_strchr(argv[i], '='))
			remove_env_value(memptr->envp, argv[i], memptr);
		i++;
	}
	return (EXIT_SUCCESS);
}
