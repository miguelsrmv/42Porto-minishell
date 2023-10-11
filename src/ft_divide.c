/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:04:08 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 14:12:53 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

static int	count_words(char *str, char divider)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == divider)
			count = count + 2;
		i++;
	}
	return (count);
}

static char	*get_next_word(char **str, char divider)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while ((*str)[len] && (*str)[len] != divider)
		len++;
	word = (char *)malloc(len + 2);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = (*str)[i];
		i++;
	}
	if ((*str)[i] == divider)
		word[i++] = divider;
	word[i] = '\0';
	*str += len + ((*str)[len] == divider);
	return (word);
}

char		**ft_divide(char *str, char divider)
{
	int		words_count;
	char	**result;
    char    *divider_string;
	int		i;

	words_count = count_words(str, divider);
	result = (char **)malloc((words_count + 1) * sizeof(char *));
    divider_string = (char *)malloc(2 * sizeof(char));
	if (!result || !divider_string)
		return (NULL);
    divider_string[0] = divider;
    divider_string[1] = '\0';
	i = 0;
        if (ft_strchr(str, divider) == str)
        {
            result[i] = ft_strdup(divider_string);
            i++;
        }
	while (i < words_count)
	{

		result[i] = get_next_word(&str, divider);
		if (!result[i])
			return (NULL);
		i++;
        if ()
            
	}
	result[i] = NULL;
    free(divider_string);
	return (result);
}
