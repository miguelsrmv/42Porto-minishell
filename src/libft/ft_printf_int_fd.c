/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:33:35 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/09 09:33:30 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_int_fd(int integer, int fd)
{
	char	*str;
	int		count;

	str = ft_itoa(integer);
	if (!str)
		return (0);
	ft_putstr_fd(str, fd);
	count = ft_strlen(str);
	free(str);
	return (count);
}
