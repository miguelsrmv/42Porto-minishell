/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:43:27 by bmota-si          #+#    #+#             */
/*   Updated: 2023/12/18 16:44:01 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr2(const char *s, int c)
{
	while (*s && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
	{
		s++;
		return ((char *)s);
	}
	return (0);
}
