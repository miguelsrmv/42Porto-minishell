/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:27:52 by bmota-si          #+#    #+#             */
/*   Updated: 2024/03/29 11:33:22 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

long	ft_atol(const char *str)
{
	long long	n;
	int			is_negative;

	n = 0;
	is_negative = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		is_negative = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		if (n * is_negative < LONG_MIN)
			return (LONG_MIN);
		else if (n * is_negative > LONG_MAX)
			return (LONG_MAX);
		str++;
	}
	while (*str && !ft_isspace(*str))
		str++;
	return ((long)(n * is_negative));
}
