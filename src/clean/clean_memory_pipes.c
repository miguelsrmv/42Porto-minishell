/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:47:20 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 09:59:57 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input(char *input, t_memptr memptr)
{
	if (input)
		free(input);
	clean_memory(&memptr);
	if (memptr.envp)
		ft_free_tabs((void **)memptr.envp);
}
