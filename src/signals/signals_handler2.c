/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:31:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 16:11:04 by mde-sa--         ###   ########.fr       */
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
	g_status_flag = 130;
	printf("> ^C\n");
	exit(g_status_flag);
	return ;
}
