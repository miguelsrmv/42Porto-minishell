/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:31:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 18:02:40 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signum)
{
	(void)signum;
	printf("Quit (Core duped)\n");
	return ;
}

void	sigquit_handler2(int signum)
{
	(void)signum;
	return ;
}

void	sigint_handler_heredocs(int signum)
{
	(void)signum;
	g_status_flag = 8;
	write(1, "> ^C\n", 5);
	exit(g_status_flag);
	return ;
}
