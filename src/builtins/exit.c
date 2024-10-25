/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/25 15:41:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	modulo_value(long value)
{
	int	exit_value;

	exit_value = value % 256;
	if (exit_value < 0)
		exit_value += 256;
	return (exit_value);
}

static char	*trim_arg(char *string, t_memptr *memptr)
{
	int		left;
	int		right;
	int		sign;
	char	*trimmed_string;

	left = 0;
	right = ft_strlen(string) - 1;
	sign = 0;
	while (ft_isspace(string[left]))
		left++;
	if (string[left] == '-')
		sign++;
	left += sign;
	while (string[left] == '0')
		left++;
	while (right > left && ft_isspace(string[right]))
		right--;
	trimmed_string = (char *)malloc(sizeof(char) * (right - left + sign + 2));
	if (!trimmed_string)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	if (sign)
		trimmed_string[0] = '-';
	ft_memcpy(&trimmed_string[sign], &string[left], right - left + 1);
	trimmed_string[right - left + 1 + sign] = '\0';
	return (trimmed_string);
}

static bool	is_a_long(char *string)
{
	if (!ft_isnumber(string) || ft_strlen(string) > 19
		|| ft_atoll(string) < LONG_MIN || ft_atoll(string) > LONG_MAX
		|| (ft_strlen(string) == 1 && ft_issign(string[0])))
		return (false);
	return (true);
}

int	ft_exit(char **args, char **envp, t_command_table *current,
		t_memptr *memptr)
{
	char	*trimmed_arg;

	printf("exit\n");
	if (ft_tablen((void **)args) == 1)
		final_clear_and_exit(*memptr, envp, memptr->pipe_fd, current);
	trimmed_arg = trim_arg(args[1], memptr);
	if (!is_a_long(trimmed_arg))
	{
		free(trimmed_arg);
		printf("exit: %s: a numeric argument is required\n", args[1]);
		g_status_flag = 2;
		final_clear_and_exit(*memptr, envp, memptr->pipe_fd, current);
	}
	g_status_flag = modulo_value(ft_atol(trimmed_arg));
	free(trimmed_arg);
	if (ft_tablen((void **)(args)) == 2)
		final_clear_and_exit(*memptr, envp, memptr->pipe_fd, current);
	printf("exit: too many arguments\n");
	g_status_flag = 1;
	return (g_status_flag);
}
