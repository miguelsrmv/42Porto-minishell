/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_single_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/20 18:18:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_builtin(t_command_table *current, char **envp,
		t_memptr *memptr)
{
	int	original_stdin;
	int	original_stdout;

	current->command_no = 1;
	if (current->valid_command == FALSE)
		return (g_status_flag);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	set_redirs(NULL, &current, *memptr);
	if (current->input_fd)
		close(current->input_fd);
	if (current->output_fd)
		close(current->output_fd);
	if (!ft_strcmp(current->cmd[0], "exit"))
		close_exit_fds(original_stdin, original_stdout);
	g_status_flag = execute_builtin(current, envp, memptr);
	close_exit_fds(original_stdin, original_stdout);
	return (g_status_flag);
}

int	execute_builtin(t_command_table *current, char **envp, t_memptr *memptr)
{
	int	(*function_pointer)(char **, char **, t_command_table *, t_memptr *);

	function_pointer = (int (*)(char **, char **, t_command_table *,
				t_memptr *))current->builtin_pointer;
	g_status_flag = function_pointer(current->cmd, envp, current, memptr);
	return (g_status_flag);
}

void	close_exit_fds(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
