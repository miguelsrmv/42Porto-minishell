/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:33:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/08 19:35:49 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	extern enum e_SignalType	g_signal_flag;

	(void)signum;
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell: ", 12);
	g_signal_flag = SIGINT_SIGNAL;
}

void	sigint_handler_during_processes_child(int signum)
{
	exit(128 + signum);
}

void	sigint_handler_during_processes_parent(int signum)
{
	extern enum e_SignalType	g_signal_flag;

	g_signal_flag = SIGINT_SIGNAL;
	write(STDOUT_FILENO, "\n", 1);
	(void)signum;
}