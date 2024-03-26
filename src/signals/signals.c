/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:18:12 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/26 14:34:38 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signal_during_processes_child(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler_child;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigquit_handler_child;
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGPIPE, sigpipe_handler);
}

void	set_signal_during_processes_parent(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler_during_processes_parent;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, sigquit_handler_parent);
}
