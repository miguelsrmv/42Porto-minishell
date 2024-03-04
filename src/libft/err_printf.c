/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:33:52 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/04 16:36:54 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	err_printf(char *string)
{
	int	original_stdout;
	int	original_stderr;
	int	len;

	original_stdout = dup(fileno(stdout));
	original_stderr = dup(fileno(stderr));
	if (dup2(fileno(stderr), fileno(stdout)) == -1)
	{
		perror("dup2");
		return (-1);
	}
	len = printf("%s", string);
	if (dup2(original_stdout, fileno(stdout)) == -1
		|| dup2(original_stderr, fileno(stderr)) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(original_stdout);
	close(original_stderr);
	return (len);
}
