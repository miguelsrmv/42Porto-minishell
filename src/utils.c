/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:07:56 by bmota-si          #+#    #+#             */
/*   Updated: 2023/12/04 18:08:07 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	check_argv_var(char **argv)
{
	if(ft_isdigit(argv[1][0]))
	{
		ft_printf("Not a valid identifier!\n");
		return(EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}