/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getppid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:17:43 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/11 17:46:29 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	get_number_from_line(char *line)
{
	int	i;
	int	number;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	number = ft_atoi(&line[i]);
	return (number);
}

int	ft_getppid(void)
{
	int		fd;
	char	*line;
	int		ppid;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line && ft_strncmp(line, "PPid:", 5))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		close(fd);
		return (-1);
	}
	ppid = get_number_from_line(line);
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (ppid);
}
