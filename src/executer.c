/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:05 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/05 15:58:35 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_command_table *current, t_env *envv_teste, t_memptr memptr)
{
	int	(*function_pointer)(char **);

	if (current->command_type == EXECUTABLE)
		execve(current->cmd_target, current->cmd, envv_teste->envp);
	else if (current->command_type == BUILTIN)
	{
		function_pointer = (int (*)(char **))current->builtin_pointer;
		//exit_value = function_pointer(current->cmd);
		function_pointer(current->cmd);
		(void)memptr;
		//clean_memory(memptr);
	}
}

/* void execute(t_command_table *current, char **envp, t_memptr memptr)
{
    int (*function_pointer)(char **);

    if (current->command_type == EXECUTABLE)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            // Trate o erro de fork
            exit_error(FORK_ERROR, memptr);
        }
        else if (pid == 0)
        {
            // Código do processo filho
            execve(current->cmd_target, current->cmd, envp);
            // Se execve falhar, trate o erro (opcional)
            exit_error("127", memptr);
        }
        else
        {
            // Código do processo pai
            int status;
            waitpid(pid, &status, 0);
            // Você pode adicionar lógica aqui para lidar com o status do filho, se necessário
        }
    }
    else if (current->command_type == BUILTIN)
    {
        function_pointer = (int (*)(char **))current->builtin_pointer;
        function_pointer(current->cmd);
        // clean_memory(memptr);
        return;
    }
}
 */