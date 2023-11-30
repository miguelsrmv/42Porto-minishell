/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:37:39 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/09 09:32:59 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_string_fd(char *string, int fd)
{
	char	*substr;
	int		count;

	if (!string)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	substr = ft_substr(string, 0, ft_strlen(string));
	if (!substr)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(substr, fd);
	count = ft_strlen(substr);
	free(substr);
	return (count);
}
