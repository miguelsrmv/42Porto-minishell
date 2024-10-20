/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:42 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 18:11:53 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char **argv, char **envp, t_command_table *current, t_memptr *memptr)
{
	(void)current;
	if (!argv[1])
		return (EXIT_SUCCESS);
	if (builtin_argument_checker(argv) == EXIT_FAILURE)
		return (g_status_flag);
	remove_env_value(&envp, argv[1], memptr);
	return (EXIT_SUCCESS);
}
