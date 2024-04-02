/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:33:12 by bmota-si          #+#    #+#             */
/*   Updated: 2024/04/02 09:32:25 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *command, char **envp, t_command_table *current,
			t_memptr memptr)
{
	(void)command;
	if (ft_exit_status(current) == 1)
	{
		if (g_status_flag == 0)
			(g_status_flag = 1);
		return (g_status_flag);
	}
	final_clear_and_exit(memptr, envp, NULL, NULL);
	return (0);
}

static char	*posnum(char *str, long long n, int len)
{
	long	x;

	len--;
	x = n;
	while (len >= 0)
	{
		str[len] = x % 10 + '0';
		x = x / 10;
		len--;
	}
	return (str);
}

static char	*negnum(char *str, long long n, int len)
{
	long	x;

	x = n;
	str[0] = '-';
	len--;
	x = x * (-1);
	while (len > 0)
	{
		str[len] = (x % 10) + '0';
		x = x / 10;
		len--;
	}
	return (str);
}

static int	int_len(long long n)
{
	int		i;
	long	x;

	x = n;
	i = 0;
	if (x <= 0)
	{
		x = x *(-1);
		i++;
	}
	while (x > 0)
	{
		x = x / 10;
		i++;
	}
	return (i);
}

char	*ft_ltoa(long long n)
{
	char	*str;
	int		len;

	len = int_len(n);
	str = (char *) malloc (sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str = negnum(str, n, len);
	}
	else if (n == 0)
		str[0] = '0';
	else
		str = posnum(str, n, len);
	return (str);
}
