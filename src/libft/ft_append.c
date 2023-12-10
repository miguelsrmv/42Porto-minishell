/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:32:41 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/10 15:32:43 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append(char **dst, char *src)
{
	char	*dst_buf;
	char	*appendet;
	int		appendet_len;

	if (dst == NULL)
		dst_buf = NULL;
	else
		dst_buf = *dst;
	appendet_len = ft_strlen(dst_buf) + ft_strlen(src);
	if (appendet_len == 0)
	{
		ft_free((void *)dst);
		return (NULL);
	}
	appendet = malloc((appendet_len + 1) * sizeof(*appendet));
	if (appendet == NULL)
		return (NULL);
	while (dst_buf && *dst_buf)
		*appendet++ = *dst_buf++;
	while (src && *src)
		*appendet++ = *src++;
	*appendet = '\0';
	ft_free((void *)dst);
	return (appendet - appendet_len);
}
