/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_input_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:14:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/27 18:34:41 by mde-sa--         ###   ########.fr       */
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

void	check_input(t_command_table **command)
{
	int	i;
	int	file_fd;

	i = 0;
	while ((*command)->full_input[i])
	{
		if (redir_check((*command)->full_input[i]) != INVALID)
			i++;
		else
		{
			(*command)->validity = INVALID_INPUT_REDIR;
			return ;
		}
		file_fd = open((*command)->full_input[i], O_RDONLY);
		if (redir_check((*command)->full_input[i - 1]) == INPUT
			&& file_fd == -1)
		{
			(*command)->validity = INVALID_INPUT;
			return ;
		}
		close(file_fd);
		i++;
	}
	(*command)->validity = VALID;
}

void	check_output(t_command_table **command)
{
	int	i;

	i = 0;
	while ((*command)->full_output[i])
	{
		if (redir_check((*command)->full_output[i]) != INVALID)
			i++;
		else
		{
			(*command)->validity = INVALID_OUTPUT_REDIR;
			return ;
		}
		i++;
	}
	(*command)->validity = VALID;
}
