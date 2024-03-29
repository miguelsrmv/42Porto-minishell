/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:12:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 13:16:43 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_shelllevel(int shell_level, t_memptr *memptr)
{
	char	*level_full_string;
	char	*level_string;

	level_string = ft_itoa(shell_level);
	level_full_string = ft_strjoin("SHLVL=", level_string);
	if (!shell_level)
	{
		free(level_string);
		exit_error(MALLOC_ERROR, *memptr, NULL);
	}
	free(level_string);
	return (level_full_string);
}

void	update_shell_level(char ***envp, t_memptr *memptr)
{
	char	*shell_level;
	int		shell_level_num;

	shell_level = return_shell_level_from_envp(*envp, memptr);
	if (shell_level == NULL)
	{
		shell_level = var_shelllevel(1, memptr);
		add_shell_level_to_envp(envp, memptr, shell_level);
	}
	else
	{
		shell_level_num = ft_atol(shell_level);
		shell_level = var_shelllevel(shell_level_num + 1, memptr);
		add_shell_level_to_envp(envp, memptr, shell_level);
	}
	memptr->envp = *envp;
}

char	*return_shell_level_from_envp(char **envp, t_memptr *memptr)
{
	int		i;
	char	*shell_level;

	i = 0;
	shell_level = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			shell_level = ft_strdup(&envp[i][6]);
			if (!shell_level)
				exit_error(MALLOC_ERROR, *memptr, NULL);
			break ;
		}
		i++;
	}
	return (shell_level);
}

void	add_shell_level_to_envp(char ***envp, t_memptr *memptr, char *shell_level)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)malloc((ft_tablen((void **)*envp) + 2) * (sizeof(char *)));
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
	new_envp[i] = shell_level;
	if (!new_envp[i++])
		{
			ft_free_tabs((void **)new_envp);
			exit_error(MALLOC_ERROR, *memptr, NULL);
		}
	new_envp[i] = NULL;
	ft_free_tabs((void **)(*envp));
	*envp = new_envp;
}
