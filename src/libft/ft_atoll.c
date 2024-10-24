/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:13:41 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/24 21:35:01 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <stdlib.h>
** SYNOPSIS: Convert a string into an long long
** DESCRIPTION: converts the initial portion of the string pointed to by str
** 				to in
** RETURN VALUE: The converted value or 0 on error.
*/

#include "libft.h"

static long long	max_value(int sign)
{
	if (sign == 1)
		return (LLONG_MAX);
	else
		return (LLONG_MIN);
}

long long	ft_atoll(const char *nptr)
{
	long long	n;
	long long	sign;

	n = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (n > (LLONG_MAX / 10) || (n == LLONG_MAX / 10 && (*nptr
					- '0') > (LLONG_MAX % 10)))
			return (max_value(sign));
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}
