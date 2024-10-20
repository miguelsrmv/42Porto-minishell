/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:12:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 18:00:48 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shell_level(char ***envp, t_memptr *memptr)
{
	int		i;
	char	*shell_level;
	int		level;

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], "SHLVL=", 6))
		{
			shell_level = ft_strdup(&(*envp)[i][6]);
			if (!shell_level)
				exit_error(MALLOC_ERROR, *memptr, NULL);
			if (ft_isnumber(shell_level))
			{
				level = ft_atol(shell_level) + 1;
				replace_shell_level(&(*envp)[i], memptr, level);
			}
			else
				replace_shell_level(&(*envp)[i], memptr, 1);
			free(shell_level);
			return ;
		}
		i++;
	}
	add_shell_level(envp, memptr);
}

void	replace_shell_level(char **envp, t_memptr *memptr, long level)
{
	char	*shell_level;
	char	*temp;

	if (level < 0)
		level = 0;
	shell_level = ft_ltoa(level);
	temp = *envp;
	*envp = ft_strjoin("SHLVL=", shell_level);
	if (!*envp)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	free(temp);
	free(shell_level);
}

void	add_shell_level(char ***envp, t_memptr *memptr)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)malloc(sizeof(char *)
			* (ft_tablen((void **)*envp) + 2));
	if (!new_envp)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (!new_envp[i++])
		{
			ft_free_tabs((void **)new_envp);
			exit_error(MALLOC_ERROR, *memptr, NULL);
		}
	}
	new_envp[i++] = ft_strdup("SHLVL=1");
	new_envp[i] = NULL;
	ft_free_tabs((void **)(*envp));
	(*envp) = new_envp;
}
