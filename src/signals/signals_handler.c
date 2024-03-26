/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:33:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/26 13:15:06 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status_flag = SIGINT_SIGNAL;
}

void	sigint_handler_child(int signum)
{
	(void)signum;
	g_status_flag = SIGINT_SIGNAL;
	exit(g_status_flag);
}

void	sigquit_handler_child(int signum)
{
	(void)signum;
	g_status_flag = SIGQUIT_SIGNAL;
	exit(g_status_flag);
}

void	sigpipe_handler(int signum)
{
	(void)signum;
	return ;
}

void	sigquit_handler_parent(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "Quit\n", 5);
	return ;
}
