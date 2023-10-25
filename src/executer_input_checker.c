/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_input_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:14:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/25 16:20:13 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_RedirectType	redir_check(char *redir_str)
{
	if (ft_strlen(redir_str) == 1 && !ft_strncmp("<", redir_str, 1))
		return (INPUT);
	else if (ft_strlen(redir_str) == 2 && !ft_strncmp("<<", redir_str, 2))
		return (HERE_DOC);
	else if (ft_strlen(redir_str) == 1 && !ft_strncmp(">", redir_str, 1))
		return (OUTPUT);
	else if (ft_strlen(redir_str) == 2 && ! ft_strncmp(">>", redir_str, 2))
		return (APPEND);
	else
		return (INVALID);
}

void	check_input(t_command_table **cmd_table)
{
	int	i;
	int	file_fd;

	i = 0;
	while ((*cmd_table)->full_input[i])
	{
		if (redir_check((*cmd_table)->full_input[i]) != INVALID)
			i++;
		else
		{
			(*cmd_table)->validity = INVALID_INPUT_REDIR;
			return ;
		}
		file_fd = open((*cmd_table)->full_input[i], O_RDONLY);
		if (file_fd == -1)
		{
			(*cmd_table)->validity = INVALID_INPUT;
			return ;
		}
		close(file_fd);
		i++;
	}
	(*cmd_table)->input_target = ft_strdup((*cmd_table)->full_input[i - 1]);
	(*cmd_table)->input_type = redir_check((*cmd_table)->full_input[i - 2]);
	(*cmd_table)->validity = VALID;
}

void	check_output(t_command_table **cmd_table)
{
	int	i;

	i = 0;
	while ((*cmd_table)->full_output[i])
	{
		if (redir_check((*cmd_table)->full_output[i]) != INVALID)
			i++;
		else
		{
			(*cmd_table)->validity = INVALID_OUTPUT_REDIR;
			return ;
		}
		i++;
	}
	(*cmd_table)->output_target = ft_strdup((*cmd_table)->full_output[i - 1]);
	(*cmd_table)->output_type = redir_check((*cmd_table)->full_output[i - 2]);
}
