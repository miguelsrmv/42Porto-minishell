/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:31:44 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/22 13:14:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *string, int type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = string;
	node->type = type;
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


void	clear_lexer_list(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	clear_command_table(t_command_table **lst)
{
	t_command_table	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
