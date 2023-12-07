/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/07 10:55:30 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_SignalType	g_signal_flag = NO_SIGNAL;
t_env				*g_env_global_ptr;

t_memptr	initialize_memptr(t_token **lexer_list,
				t_command_table **command_table, 
					char **envp_cpy)
{
	t_memptr	memptr;

	memptr.lexer_list = lexer_list;
	memptr.command_table = command_table;
	memptr.envp_cpy = envp_cpy;
	memptr.path_list = NULL;
	memptr.pipe_fd = NULL;
	return (memptr);
}

void	set_environment_vars(char **envp_cpy, t_memptr memptr)
{
	t_env			*envv;

	envv = init_envv(envp_cpy);
	if (envv == NULL)
		exit_error(ENV_ERROR, memptr);
	set_envp(envp_cpy);
	set_envv(envv);

	g_env_global_ptr = envv;
	(void)g_env_global_ptr;
}

int	main(int argc, char **argv, char **envp)
{
	t_token			*lexer_list;
	t_command_table	*command_table;
	char			**envp_cpy;
	t_memptr		memptr;

	(void)argv;
	lexer_list = NULL;
	command_table = NULL;
	envp_cpy = ft_tabdup(envp);
	memptr = initialize_memptr(&lexer_list, &command_table, envp_cpy);
	if (argc > 1 || !ft_strcmp(argv[0], "./minishell"))
		exit_error(USAGE_ERROR, memptr);
	bash_main(envp_cpy, memptr);
	return (0);
}
