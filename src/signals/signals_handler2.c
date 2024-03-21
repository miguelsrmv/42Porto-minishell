/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:31:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/21 23:42:24 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	sigint_handler_inputs(int signum)
{
	(void)signum;
	close(g_status_flag);
	g_status_flag = 8;
	write(1, "> ^C\n", 5);
	exit(g_status_flag);
}
