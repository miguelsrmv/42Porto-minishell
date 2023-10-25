/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_input_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:14:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/25 10:52:14 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_redir(char *redir_str)
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

void	check_input(t_command_table **command_table)
{
	int	i;
	int	file_fd;

	i = 0;
	while (full_input[i])
	{
		if (is_valid_redir(full_input[i]) != INVALID)
			i++;
		else
		{
			(*command_table)->validity = INVALID_INPUT_REDIR;
			return ;
		}
		file_fd = open(full_input[i], O_RDONLY);
		if (file_fd == -1)
		{
			(*command_table)->validity = INVALID_INPUT;
			return ;
		}
		close(file_fd);
		i++;
	}
	(*command_table)->input_target = ft_strdup(full_input[i - 1]);
	(*command_table)->input_type = is_valid_redir(full_input[i - 2]);
	(*command_table)->validity = VALID;
}

void	check_output(t_command_table **command_table)
{
	int	i;

	i = 0;
	while (full_output[i])
	{
		if (is_valid_redir(full_output[i]) != INVALID)
			i++;
		else
		{
			(*command_table)->validity = INVALID_OUTPUT_REDIR;
			return ;
		}
		i++;
	}
	(*command_table)->output_target = ft_strdup(full_output[i - 1]);
	(*command_table)->output_type = is_valid_redir(full_output[i - 2]);
}
