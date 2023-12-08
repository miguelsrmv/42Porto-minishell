/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:46:45 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/08 19:16:36 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_envp(int *envv_pipe, char **envp, t_memptr memptr)
{
	int							tab_len;
	int							str_len;

	(void)memptr;
	close(envv_pipe[0]);
	tab_len = 0;
	while (envp[tab_len])
		tab_len++;
	write(envv_pipe[1], &tab_len, sizeof(int));
	tab_len = 0;
	while (envp[tab_len])
	{
		str_len = ft_strlen(envp[tab_len]);
		write(envv_pipe[1], &str_len, sizeof(int));
		write(envv_pipe[1], envp[tab_len], str_len + 1);
		tab_len++;
	}
	close(envv_pipe[1]);
}

void	read_envp(int *envp_pipe, char ***envp_cpy, t_memptr *memptr)
{
	int							tab_len;

	if (close(envp_pipe[1]) == -1)
		exit_error(CLOSE_ERROR, *memptr);
	tab_len = 0;
	if (read(envp_pipe[0], &tab_len, sizeof(int)) == -1)
		exit_error(READ_ERROR, *memptr);
	ft_free_tabs((void **)*envp_cpy);
	*envp_cpy = NULL;
	*envp_cpy = (char **)malloc((tab_len + 1) * sizeof(char *));
	if (!(*envp_cpy))
		exit_error(MALLOC_ERROR, *memptr);
	read_subenvp(envp_pipe, *envp_cpy, memptr, tab_len);
	if (close(envp_pipe[0]) == -1)
		exit_error(CLOSE_ERROR, *memptr);
}

void	read_subenvp(int *envp_pipe, char **envp_cpy,
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
