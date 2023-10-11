/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:20:52 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 12:20:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char *ft_strndup(const char *src, size_t n)
{
    char *cpy;
    size_t i;

    i = 0;
    while (src[i] && i < n) {
        i++;
    }
    cpy = (char *)malloc(sizeof(char) * i + 1);
    if (!cpy) {
        return (NULL);
    }
    i = 0;
    while (*src && i < n) {
        cpy[i++] = *src++;
    }
    cpy[i] = '\0';
    return (cpy);
}
