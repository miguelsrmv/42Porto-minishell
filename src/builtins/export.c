/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/24 11:59:10 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp, t_memptr *memptr)
{
	int		i;
	int		key_length;
	char	*equals_sign;
	char	**envp_cpy;

	envp_cpy = ft_tabdup(envp);
	if (!envp_cpy)
		exit_error(MALLOC_ERROR, *memptr, NULL);
	i = 0;
	bubble_sort(envp_cpy);
	while ((envp_cpy)[i])
	{
		equals_sign = ft_strchr(envp_cpy[i], '=');
		if (equals_sign)
		{
			key_length = equals_sign - envp_cpy[i];
			printf("-declare -x %.*s=\"%s\"\n", key_length, envp_cpy[i],
				equals_sign + 1);
		}
		else
			printf("-declare -x %s\n", envp_cpy[i]);
		i++;
	}
	ft_free_tabs((void **)envp_cpy);
}

bool	export_is_invalid(char *argument)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argument[i]) && argument[i] != '_')
		return (true);
	i++;
	while (argument[i] && argument[i] != '=')
	{
		if (!ft_isalnum(argument[i]) && argument[i] != '_')
			return (true);
		i++;
	}
	return (false);
}

void	add_to_export_list(char *argument, char **envp, t_memptr *memptr)
{
	char	*key;
	char	*value;
	char	*equal_position;

	if (export_is_invalid(argument))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(argument, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_status_flag = 1;
		return ;
	}
	equal_position = ft_strchr(argument, '=');
	if (equal_position)
	{
		key = ft_substr(argument, 0, equal_position - argument);
		value = equal_position + 1;
	}
	else
	{
		key = ft_strdup(argument);
		value = NULL;
	}
	set_env_value(envp, key, value, memptr);
	free(key);
}

int	export(char **argv, char **envp, t_command_table *current, t_memptr *memptr)
{
	int	i;

	(void)current;
	(void)memptr;
	if (builtin_argument_checker(argv) == EXIT_FAILURE)
		return (g_status_flag);
	else if (!argv[1])
	{
		print_export(envp, memptr);
		return (EXIT_SUCCESS);
	}
	else
	{
		g_status_flag = EXIT_SUCCESS;
		i = 1;
		while (argv[i])
		{
			add_to_export_list(argv[i], memptr->envp, memptr);
			i++;
		}
	}
	return (g_status_flag);
}

// TODO: Check what happens if there is
// an invalid export in the middle of valid exports!
// example: export a=1 b=3 w      = 3    z=5
// including status signals!
// also, exporting does not requrie a =
// however, it does require stuff in the beggining to not be a digit
