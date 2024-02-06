/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:53:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/06 17:55:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_last_char(const char *string)
{
	int	i;

	if (!string)
		return ('\0');
	i = ft_strlen(string);
	i--;
	return (string[i]);
}
