/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:34 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/05 12:38:11 by bmota-si         ###   ########.fr       */
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
		if (split[0])
		{
			var = ft_strdup(split[0]);
			ft_free_str_array(&split);
		}
		if (var == NULL)
			return (EXIT_FAILURE);
		if (export_error_loop(&var, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
		ft_free_str(&var);
	}
	return (EXIT_SUCCESS);
}

int	check_argv_var(char *argv)
{
	int		i;

	i = 0;
	if (!ft_isalpha(argv[0]) && argv[0] != '_' && argv[0] != '|')
	{
		ft_printf("minishell: '%c' Not a valid identifier!\n", argv[0]);
		//g_status_flag = 1;
		return (EXIT_FAILURE);
	}
	if (argv[0] == '_' && argv[1] == '\0')
		return (EXIT_FAILURE);
	while(argv[i] != '\0' && argv[i] != '=')
	{
		if(argv[i] == '-' || argv[i] == '+')
			return(EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
