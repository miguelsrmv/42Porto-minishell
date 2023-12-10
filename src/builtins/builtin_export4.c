/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:34 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/29 17:24:35 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_error_loop(char **var, char **argv)
{
	int	j;

	j = 0;
	while ((*var)[j] != '\0')
	{
		if (ft_isalnum((*var)[j]) == 0 && (*var)[j] != '_')
		{
			ft_fprintf(2, "export: %s: not a valid identifier\n", argv[1]);
			ft_free_str(var);
			return (EXIT_FAILURE);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int	export_input_error(char **argv)
{
	char	**split;
	char	*var;
	int		i;

	i = 1;
	var = NULL;
	while (argv && argv[i])
	{
		split = ft_split(argv[i], '=');
		if (split == NULL)
			return (EXIT_FAILURE);
		var = ft_strdup(split[0]);
		ft_free_str_array(&split);
		if (var == NULL)
			return (EXIT_FAILURE);
		if (export_error_loop(&var, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
		ft_free_str(&var);
	}
	return (EXIT_SUCCESS);
}
