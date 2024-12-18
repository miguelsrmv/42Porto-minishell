/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/26 12:06:10 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int			g_status_flag;

t_memptr	initialize_memptr(t_token **lexer_list,
		t_command_table **command_table, char **argv, char **envp)
{
	t_memptr	memptr;

	memptr.lexer_list = lexer_list;
	memptr.command_table = command_table;
	memptr.first_node = NULL;
	memptr.path_list = NULL;
	memptr.pipe_fd = NULL;
	memptr.argc = ft_tablen((void **)argv);
	memptr.argv = argv;
	memptr.envp = envp;
	memptr.return_value = 0;
	memptr.my_pwd = NULL;
	memptr.my_oldpwd = NULL;
	memptr.unset_pwd_flag = 0;
	return (memptr);
}

int	main(int argc, char **argv, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	t_memptr		memptr;
	char			**envp_cpy;

	if (argc > 1 || envp == NULL || envp[0] == NULL)
	{
		printf("Usage error.\n");
		return (1);
	}
	lexer_list = NULL;
	command_table = NULL;
	envp_cpy = ft_tabdup(envp);
	if (!envp_cpy)
	{
		ft_putstr_fd(MALLOC_ERROR, STDERR_FILENO);
		return (1);
	}
	memptr = initialize_memptr(&lexer_list, &command_table, argv, envp_cpy);
	bash_main(&memptr);
	return (0);
}
