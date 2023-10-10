/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/10 14:02:49 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{	
	t_minishell shell;
	
	// Get string from readline (include readline)
	char *buffer;
	
	//ft_init_struct(&shell);
	
	while(1)
	{
		buffer = readline("minishell$: ");
		//ft_printf("\nYou typed in \"%s\".\n\n", buffer);
		
		if (buffer == NULL) {
            // O usuário pressionou Ctrl+D, então saímos do loop
            break;
        }
		
		if (buffer[0] != '\0')
		{
            add_history(buffer);

            // Splits buffer, ignorando aspas
            char **splitted_buffer = ft_command_split(buffer);

            if (splitted_buffer[0] != NULL) 
			{
                // Verifica se o comando é "exit" para sair do shell
                if (strcmp(splitted_buffer[0], "exit") == 0) 
				{
                    free(buffer);
                    break;
                }

                // Executa o comando
                pid_t child_pid = fork();

                if (child_pid == -1) 
				{
                    perror("fork");
                } 
				else if (child_pid == 0) 
				{
                    // Este é o processo filho

                    // Obtém o caminho completo para o comando usando execução no ambiente atual
                    char *command_path = NULL;
                    command_path = getenv("PATH");
                    command_path = strtok(command_path, ":");

                    while (command_path != NULL) 
					{
                        char *full_command = malloc(strlen(command_path) + strlen(splitted_buffer[0]) + 2);
                        sprintf(full_command, "%s/%s", command_path, splitted_buffer[0]);

                        execve(full_command, splitted_buffer, envp);
                        perror("execve");

                        free(full_command);
                        command_path = strtok(NULL, ":");
                    }

                    // Se chegarmos aqui, a execução falhou
                    //fprintf(stderr, "Comando não encontrado: %s\n", splitted_buffer[0]);
                    exit(EXIT_FAILURE);
                }
				else 
				{
                    // Este é o processo pai, espera pelo filho
                    int status;
                    waitpid(child_pid, &status, 0);
                }
			}

		/*// Splits buffer, ignoring quotes
		char **splitted_buffer;
		splitted_buffer = ft_command_split(buffer);
		ft_printf("List of words:\n");
		while (*splitted_buffer)
		{
			ft_printf("%s\n", *splitted_buffer);
			splitted_buffer++;
		}

		// Get current directory (include unistd & limits.h)
		char *current_dir;
		current_dir = NULL;	
		current_dir = getcwd(current_dir, PATH_MAX + 1);
		ft_printf("\nYou're on directory %s\n\n", current_dir);

		// Get list of PATHs (include stdlib)
		char *path;
		char **path_list;
		path = getenv("PATH");
		path_list = ft_split(path, ':');
		ft_printf("List of paths:\n");
		while (*path_list)
		{
			ft_printf("%s\n", *path_list);
			path_list++;
		}*/
	}
	}
	rl_clear_history();
}
