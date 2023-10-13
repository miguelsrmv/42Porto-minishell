/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:31:44 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/13 19:57:26 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *string)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = string;
	node->next = NULL;
	return (node);
}

t_token	*last_token(t_token *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	add_token_end(t_token **list, t_token *new)
{
	t_token	*last_node;

	if (*list == NULL)
		*list = new;
	else
	{
		last_node = last_token(*list);
		last_node->next = new;
	}
}
