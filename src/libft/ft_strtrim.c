/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:40:49 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/19 15:21:22 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc(3)) and returns a copy of ’s1’
** with the characters specified in ’set’ removed from the beginning
** and the end of the string.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (*s1 && ft_strrchr(set, s1[i]))
		i--;
	str = ft_substr(s1, 0, i + 1);
	return (str);
}

/* char	*ft_strtrim(char const *s1, char const *set)
{
    char *str;
    size_t i;

    while (*s1 && ft_strchr(set, *s1))
        s1++;
    i = ft_strlen(s1);
    while (*s1 && ft_strrchr(set, s1[i]))
        i--;

    // Liberar a memória original antes de alocar a nova string
    char *original = ft_strdup(s1);  // fazer uma cópia da string original
    if (!original)
        return (NULL);

    // Alocar a nova string
    str = ft_substr(original, 0, i + 1);

    // Liberar a memória da cópia original
    free(original);

    return (str);
} */
