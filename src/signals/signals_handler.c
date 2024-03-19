/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:33:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/19 20:34:11 by mde-sa--         ###   ########.fr       */
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

void	sigquit_handler(int signum)
{
	(void)signum;
	printf("Quit (Core duped)\n");
	return ;
}

void	sigpipe_handler(int signum)
{
	(void)signum;
	return ;
}
