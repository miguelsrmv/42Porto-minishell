/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:33:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/29 13:10:00 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	extern int	g_status_flag;

	(void)signum;
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell: ", 12);
	g_status_flag = NO_SIGNAL;
}

void	sigint_handler_during_processes_child(int signum)
{
	extern int	g_status_flag;

	(void)signum;
	g_status_flag = SIGINT_SIGNAL;
}

void	sigint_handler_during_processes_parent(int signum)
{
	extern int	g_status_flag;

	(void)signum;
	g_status_flag = NO_SIGNAL;
	write(STDOUT_FILENO, "\n", 1);
}
