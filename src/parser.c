/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:13:32 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/17 12:22:03 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *lexer_list)
{
	return (VALID);
}

t_command_table	*parse_list(t_token *lexer_list)
{
	t_command_table	*command_table;

	if (check_syntax(lexer_list) == INVALID)
		exit_error("Syntax error\n");
	command_table = NULL;
	return (command_table);
}
