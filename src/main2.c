#include "minishell.h"

char    *ft_strtok(char *str)
{
    static int count = 1;
    int i = 0;
    int j = 0;
    int x = 0;
    char *str2;

    str2 = malloc(sizeof(char) * ft_strlen(str));
    while(x < count)
    {
        j = 0;
        /* if(str[i] == '\0')
            exit(0); */
        if(str[i] == ':')
            i++;
        while(str[i] != ':')
        {
            str2[j] = str[i];
            i++;
            j++;
        }
        x++;
    }
    str2[j] = '\0';
    count++;
    return (str2);

}

int	main(int argc, char **argv, char **envp)
{
    t_minishell shell;
    char *buffer;

    while(1)
    {
        ft_init_struct(&shell);
        shell.init_str = readline("minishell$: ");

        if(shell.init_str == NULL)
            break;
        
        if(shell.init_str[0] != '\0')
        {
            add_history(shell.init_str);
            // Splits buffer, ignorando aspas
            shell.args = ft_command_split(shell.init_str);

            // Verifica se o comando é "exit" para sair do shell
            if (strcmp(shell.args[0], "exit") == 0) 
            {
                free(shell.init_str);
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
                shell.command = getenv("PATH");
                //FT_strtok copia o Path ate aos ":" para o shell.command
                shell.command = ft_strtok(shell.command);

                while (shell.command != NULL) 
                {
                    char *full_command = malloc(strlen(shell.command) + strlen(shell.args[0]) + 2);
                    sprintf(full_command, "%s/%s", shell.command, shell.init_str);

                    if(strcmp(shell.args[0], "pwd") == 0)
                    {
                        execute_pwd(shell.args[0]);
                    }
                    else
                        execve(full_command, shell.args, NULL);
                    //perror("execve");

                    free(full_command);
                    shell.command = ft_strtok(getenv("PATH"));
                }
                // Se chegarmos aqui, a execução falhou
                //fprintf(stderr, "Comando não encontrado: %s\n", splitted_buffer[0]);
            }
            else
            {
                // Este é o processo pai, espera pelo filho
                int status;
                waitpid(child_pid, &status, 0);
            }
        }
    }
}