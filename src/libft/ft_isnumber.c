/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:33:00 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 12:40:45 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *string)
{
	int	return_value;
	int	i;

	return_value = 1;
	i = 0;
	if (string[0] == '+' || string[0] == '-')
		i++;
	if (string[0] == '-')
		return_value = -1;
	while (string[i])
	{
		if (!ft_isdigit((int)string[i]))
			return (0);
		i++;
	}
	return (return_value);
}
