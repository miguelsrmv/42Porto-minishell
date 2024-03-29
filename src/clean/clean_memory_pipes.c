/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:47:20 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 15:53:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input(char *input, t_memptr memptr)
{
	t_env	*envv;

	if (input)
		free(input);
	clean_memory(&memptr);
	if (memptr.envp)
		ft_free_tabs((void **)memptr.envp);
	envv = get_envv();
	free_envv(envv);
}
