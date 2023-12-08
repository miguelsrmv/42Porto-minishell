/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_prepare_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:25:11 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/08 15:54:01 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_next_command(char **envp_cpy, t_memptr	*memptr)
{
	/*
	extern enum e_SignalType	g_signal_flag;

 	char *message = ft_strjoin(ft_strjoin("\nPreparing NEXT process, signal is ", ft_itoa(g_signal_flag)), "\n");
	int message_len = ft_strlen(message);
	write(2, message, message_len);

	if (g_signal_flag == NO_SIGNAL)	
		read_envv(envp_pipe, envp_cpy, memptr);
	else if (g_signal_flag == SIGINT_SIGNAL)
	{
		if (close(envp_pipe[0]) == -1)
			exit_error(CLOSE_ERROR, *memptr);
		if (close(envp_pipe[1]) == -1)
			exit_error(CLOSE_ERROR, *memptr);
		g_signal_flag = NO_SIGNAL;
	}
	else if (g_signal_flag == EOF_SIGNAL)
		exit_error(EOF_ERROR, *memptr);
	clean_memory(*memptr); */
	(void)envp_cpy;
	(void)memptr;
	return ;
}

void	read_envv(int *envp_pipe, char ***envp_cpy, t_memptr *memptr)
{
	extern enum e_SignalType	g_signal_flag;
	int							tab_len;

	if (close(envp_pipe[1]) == -1)
		exit_error(CLOSE_ERROR, *memptr);
	if (g_signal_flag == SIGINT_SIGNAL)
	{
		if (close(envp_pipe[0]) == -1)
			exit_error(CLOSE_ERROR, *memptr);
		return ;
	}
	tab_len = 0;
	if (read(envp_pipe[0], &tab_len, sizeof(int)) == -1)
		exit_error(READ_ERROR, *memptr);
	ft_free_tabs((void **)*envp_cpy);
	*envp_cpy = NULL;
	*envp_cpy = (char **)malloc((tab_len + 1) * sizeof(char *));
	if (!(*envp_cpy))
		exit_error(MALLOC_ERROR, *memptr);
	read_subenvv(envp_pipe, *envp_cpy, memptr, tab_len);
	if (close(envp_pipe[0]) == -1)
		exit_error(CLOSE_ERROR, *memptr);
}

void	read_subenvv(int *envp_pipe, char **envp_cpy,
			t_memptr *memptr, int tab_len)
{
	int	str_len;
	int	i;

	str_len = 0;
	i = 0;
	while (i < tab_len)
	{
		if (read(envp_pipe[0], &str_len, sizeof(int)) == -1)
			exit_error(READ_ERROR, *memptr);
		envp_cpy[i] = (char *)malloc(str_len + 1);
		if (!envp_cpy[i])
			exit_error(MALLOC_ERROR, *memptr);
		if (read(envp_pipe[0], envp_cpy[i], str_len + 1) == -1)
			exit_error(READ_ERROR, *memptr);
		envp_cpy[(i)++][str_len] = '\0';
	}
	envp_cpy[i] = NULL;
}
