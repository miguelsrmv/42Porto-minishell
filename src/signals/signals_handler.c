/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:33:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 13:19:09 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status_flag = SIGINT_SIGNAL;
}

void	sigint_handler_during_processes_child(int signum)
{
	(void)signum;
	g_status_flag = SIGINT_SIGNAL;
	printf("\n");
}

void	sigint_handler_during_processes_parent(int signum)
{
	(void)signum;
	g_status_flag = NO_SIGNAL;
	printf("\n");
}

void	sigpipe_handler(int signum)
{
	(void)signum;
	return ;
}
