/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_contract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:13:14 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/10 10:13:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	contract_double_vector(char **vector)
{
	int		vector_index;
	int		i;
	int		j;
	char	quote_status;
	char	*result;
	char	*temp;

	vector_index = 0;
	while (vector[vector_index])
	{
		result = (char *)malloc(sizeof(vector[vector_index]));
		if (!result)
			return ;
		quote_status = '\0';
		i = 0;
		j = 0;
		while ((vector[vector_index])[i])
		{
			if (ft_isquote((vector[vector_index])[i]))
			{
				quote_status = vector[vector_index][i];
				i++;
			}
			if (quote_status)
			{
				while (vector[vector_index][i] != quote_status && vector[vector_index][i])
					result[j++] = vector[vector_index][i++];
				quote_status = '\0';
				i++;
			}
			else if (!quote_status)
			{
				while (!quote_status && (vector[vector_index][i]))
				{
					result[j++] = vector[vector_index][i++];
					if (ft_isquote(vector[vector_index][i]))
						quote_status = vector[vector_index][i];
				}
			}
		}
		j++;
		result[j] = '\0';
		temp = vector[vector_index];
		vector[vector_index] = result;
		free(temp);
		vector_index++;
	}
}