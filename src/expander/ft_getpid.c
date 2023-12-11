/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:17:43 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/11 14:27:43 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpid(void)
{
	int		fd;
	char	*line;
	int		pid;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line && ft_strncmp(line, "Pid:", 4))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		close(fd);
		return (-1);
	}
	pid = get_pid_from_line(line);
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (pid);
}

int	get_pid_from_line(char *line)
{
	int	i;
	int	pid;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	pid = ft_atoi(&line[i]);
	return (pid);
}
