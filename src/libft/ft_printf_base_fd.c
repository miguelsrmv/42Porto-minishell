/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:22:52 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/09 09:34:01 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	temp;

	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa_base(unsigned int integer, char *base)
{
	char	*str;
	int		i;
	int		base_len;

	if (integer == 0)
		return (ft_strdup("0"));
	base_len = ft_strlen(base);
	i = 0;
	str = (char *)malloc((sizeof(char) * 32) + 1);
	if (!str)
		return (NULL);
	while (integer)
	{
		str[i++] = base[integer % base_len];
		integer /= base_len;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}

int	ft_printf_base_fd(int integer, char *base, int fd)
{
	char	*str;
	int		count;

	str = ft_itoa_base((unsigned int)integer, base);
	if (!str)
		return (0);
	ft_putstr_fd(str, fd);
	count = ft_strlen(str);
	free(str);
	return (count);
}
