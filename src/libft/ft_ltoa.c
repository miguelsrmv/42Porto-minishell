/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:17:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/24 19:17:16 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Allocate (with malloc(3)) and returns a “fresh” string ending
**  with ’\0’ representing the integer n given as argument.
**  Negative numbers must be supported. If the allocation fails,
**  the function returns NULL.
*/

#include "libft.h"

static int	digit_length_long(long n)
{
	int	digit_length;

	digit_length = 0;
	if (n <= 0)
		digit_length++;
	while (n != 0)
	{
		n = n / 10;
		digit_length++;
	}
	return (digit_length);
}

static void	fill_result_long(int len, int index, long n, char *result)
{
	while (len > index)
	{
		result[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

char	*ft_ltoa(long n)
{
	char	*result;
	int		index;
	int		len;

	index = 0;
	len = digit_length_long(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (n == LONG_MIN)
	{
		result[0] = '-';
		result[1] = '9';
		n = -(LONG_MIN + 9000000000000000000L);
		index = 2;
	}
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
		index++;
	}
	fill_result_long(len, index, n, result);
	result[len] = '\0';
	return (result);
}
