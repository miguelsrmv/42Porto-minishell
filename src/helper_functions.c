/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:53:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/26 16:35:14 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer_tokens(t_token *head)
{
	int		i;
	t_token	*current;

	current = head;
	i = 1;
	while (current)
	{
		if (current->token)
			ft_printf("Node %i: %s\t\ttype: %i\n", i++, current->token,
				current->type);
		current = current->next;
	}
}

void	print_command_table(t_command_table *command_table)
{
	int				i;
	int				j;
	t_command_table	*current;

	current = command_table;
	i = 1;
	while (current)
	{
		ft_printf("\nCOMMAND #%i:\n", i++);
		ft_printf("Command: ");
		j = 0;
		while (current->cmd[j])
			ft_printf("[%s]", current->cmd[j++]);
		ft_printf("\nFull Input: ");
		j = 0;
		while (current->full_input[j])
			ft_printf("[%s]", current->full_input[j++]);
		ft_printf("\nFull Output: ");
		j = 0;
		while (current->full_output[j])
			ft_printf("[%s]", current->full_output[j++]);
		ft_printf("\n\n");
		current = current->next;
	}
}


