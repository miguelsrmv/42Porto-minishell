/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_contract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:13:14 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/10 16:33:59 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	contract_double_vector(char **vector)
{
	int	vector_index;

	vector_index = 0;
	while (vector[vector_index])
	{
		if (ft_strchr(vector[vector_index], squote)
			|| ft_strchr(vector[vector_index], dquote))
			vector[vector_index] = take_out_quotes(vector[vector_index]);
		vector_index++;
	}
}

char	*take_out_quotes(char *string)
{
	char	*result;
	int		string_len;
	int		i;
	int		j;
	char	quote_flag;

	string_len = (int)ft_strlen(string);
	result = (char *)malloc(string_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote_flag = '\0';
	while (string[i])
	{
		if (ft_isquote(string[i]) && quote_flag == '\0')
			quote_flag = string[i];
		else if (ft_isquote(string[i]) && string[i] == quote_flag)
			quote_flag = '\0';
		if (!ft_isquote(string[i]) || (quote_flag == '\0'))
			result[j++] = string[i];
		i++;
	}
	while (j < string_len)
		result[j++] = '\0';
	return (result);
}
