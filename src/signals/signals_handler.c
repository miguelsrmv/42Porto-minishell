/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:33:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/04 12:46:14 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell: ", 12);
	g_status_flag = SIGINT_SIGNAL;
}

void	sigint_handler_during_processes_child(int signum)
{
	(void)signum;
	g_status_flag = SIGINT_SIGNAL;
}

void	sigint_handler_during_processes_parent(int signum)
{
	(void)signum;
	g_status_flag = NO_SIGNAL;
	write(STDOUT_FILENO, "\n", 1);
}
