/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_input_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:14:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/28 21:24:57 by mde-sa--         ###   ########.fr       */
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

enum e_ValidType	check_input(t_command_table **command)
{
	int	i;

	i = 0;
	while ((*command)->full_input[i])
	{
		if (redir_check((*command)->full_input[i]) != INVALID)
			(*command)->input_type = redir_check((*command)->full_input[i++]);
		else
			return (INVALID_INPUT_REDIR);
		if (access((*command)->full_input[i], F_OK) != 0)
			return (INVALID_INPUT);
		(*command)->input_target = (*command)->full_input[i++];
	}
	if ((*command)->command_no != 1 && (*command)->input_type != INPUT
		&& (*command)->input_type != HERE_DOC)
		(*command)->input_type = PIPE;
	if (!(*command)->input_target && (*command)->input_type != PIPE)
		(*command)->input_type = NONE;
	return (VALID);
}

enum e_ValidType	check_output(t_command_table **command)
{
	int	i;

	i = 0;
	while ((*command)->full_output[i])
	{
		if (redir_check((*command)->full_output[i]) != INVALID)
			(*command)->output_type = redir_check((*command)->full_output[i++]);
		else
			return (INVALID_OUTPUT_REDIR);
		(*command)->output_target = (*command)->full_output[i++];
	}
	if ((*command)->next && (*command)->output_type != OUTPUT
		&& (*command)->output_type != APPEND)
		(*command)->output_type = PIPE;
	if (!(*command)->output_target && (*command)->output_type != PIPE)
		(*command)->output_type = NONE;
	return (VALID);
}

void	set_redirections(int **pipe_fd, t_command_table **command)
{
	if ((*command)->input_type == INPUT || (*command)->input_type == HERE_DOC)
		(*command)->input_fd = open((*command)->input_target, O_RDONLY);
	else if ((*command)->input_type == PIPE)
		(*command)->input_fd = pipe_fd[(*command)->command_no - 2][0];
	if ((*command)->input_type != NONE)
		dup2((*command)->input_fd, STDIN_FILENO);
	if ((*command)->output_type == OUTPUT)
		(*command)->output_fd = open((*command)->output_target,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*command)->output_type == APPEND)
		(*command)->output_fd = open((*command)->output_target,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if ((*command)->output_type == PIPE)
		(*command)->output_fd = pipe_fd[(*command)->command_no - 1][1];
	if ((*command)->output_type != NONE)
		dup2((*command)->output_fd, STDOUT_FILENO);
	if ((*command)->command_no > 1)
		close(pipe_fd[(*command)->command_no - 2][0]);
	if ((*command)->next)
		close(pipe_fd[(*command)->command_no - 1][1]);
}

void	check_redirections(int **pipe_fd, t_command_table **command)
{
	enum e_ValidType	input_status;
	enum e_ValidType	output_status;

	input_status = check_input(command);
	output_status = check_output(command);
	if (input_status == VALID && output_status == VALID)
	{
		set_redirections(pipe_fd, command);
		return ;
	}
	else if (input_status == INVALID_INPUT_REDIR)
		ft_printf("Minishell: syntax error near unexpected token\n");
	else if (input_status == INVALID_INPUT)
		ft_printf("Minishell: %s: No such file or directory\n",
			(*command)->input_target);
	else if (output_status == INVALID_OUTPUT_REDIR)
		ft_printf("Minishell: syntax error near unexpected token\n");
	return ; // Error handling
}
