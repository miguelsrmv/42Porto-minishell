/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:18:12 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/08 16:16:19 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_main(int signum)
{
	extern enum e_SignalType	g_signal_flag;

	(void)signum;
	g_signal_flag = SIGINT_SIGNAL;
	write(2, "\n", 1);
}

void	set_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_main;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	sigint_handler_subprocess(int signum)
{
	exit(signum + SIGINT_SIGNAL);
}

void	set_subprocess_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_subprocess;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
