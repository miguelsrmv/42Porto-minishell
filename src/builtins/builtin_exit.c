/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/05 11:18:00 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_status(t_command_table *current)
{
	int	count;
	//int	status;

	count = ft_word_count(current->cmd);
	//wait(&status);
	/* if (WIFEXITED(status))
		return (exit_status2(current, count)); */
	exit_status2(current, count);
	return (0);
}

int	exit_status2(t_command_table *current, int count)
{
	if (count == 1)
	{
		printf("exit\n");
		g_status_flag = 0;
		return (0);
	}
	if (check_arg_exit(current) == 0)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: numeric argument required\n", 2);
		g_status_flag = 2;
		return (0);
	}
	if (count > 2)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_status_flag = 1;
		return (1);
	}
	else
		return (exit_status3(current));
}

int	exit_status3(t_command_table *current)
{
	long long	num;
	char		*str;

	num = ft_atol(current->cmd[1]);
	str = ft_ltoa(num);
	if (ft_strncmp(str, current->cmd[1], ft_strlen(str)) != 0)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: numeric argument required\n", 2);
		g_status_flag = 2;
		free(str);
		return (0);
	}
	free(str);
	printf("exit\n");
	num = ft_atol(current->cmd[1]);
	g_status_flag = (num % 256);
	return (0);
}

int	ft_word_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_arg_exit(t_command_table *current)
{
	int	i;

	i = 0;
	if (current->cmd[1][i] == '-' || current->cmd[1][i] == '+')
		i = 1;
	while (current->cmd[1][i])
	{
		if (!ft_isdigit(current->cmd[1][i]))
			return (0);
		i++;
	}
	current->cmd[1] = ft_strtrim(current->cmd[1], "+");
	return (1);
}
