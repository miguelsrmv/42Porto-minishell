# include "minishell.h"

int minishell_pwd(char **args)
{
    char *current_directory = getcwd(NULL, 0);
    if (current_directory == NULL)
    {
        perror("getcwd");
        return 1; // Erro
    }
    printf("%s\n", current_directory);
    free(current_directory);
    return 0; // Sucesso
}

int minishell_exit(char **args) 
{
    if (args[1] != NULL) 
    {
        int exit_status = atoi(args[1]);
        exit(exit_status);
    } else 
    {
        exit(0); // Saída sem status específico
    }
}

/* void process_escape_sequences(char *input)
{
    int input_length = strlen(input);
    int i = 0;

    while (i < input_length)
    {
        if (input[i] == '\\' && i + 1 < input_length)
        {
            // Check for specific escape sequences
            if (input[i + 1] == 'n')
            {
                ft_printf("'\n'");
                i += 2;
            } 
            else if (input[i + 1] == 't')
            {
                ft_printf("'\t'");
                i += 2;
            } 
            else
            {
                // Print the backslash and the character
                ft_printf("%s", input[i]);
                i++;
            }
        } 
        else
        {
            // Just print the character
            ft_printf("%s", input[i]);
            i++;
        }
    }
} */

int minishell_echo(char **args) {
    int i = 1;
    int skip_newline = 0;

    if (args[1] != NULL && ft_strcmp(args[1], "-n") == 0) {
        skip_newline = 1;
        i = 2;
    }

    /*else if(args[1] != NULL)
    {
        process_escape_sequences(args[1]);
    }*/

    while(args[i] != NULL)
    {
        /*if (ft_strcmp(args[i], "\n") == 0)
            ft_printf("\n");
        else*/
        ft_printf("%s", args[i]);
        if (args[i + 1] != NULL)
        {
            ft_printf(" ");
        }
        i++;
    }

    if (!skip_newline) 
    {
        printf("\n");
    }
    return 0;
}

int     minishell_cd(char **args) 
{
    if (args[1] == NULL) 
    {
        fprintf(stderr, "cd: missing argument\n");
    } 
    else 
    {
        if (chdir(args[1]) != 0) 
        {
            perror("cd");
        }
    }
    return 0;
}

int minishell_env(char **env) 
{
    while (*env != NULL) {
        ft_printf("%s\n", *env);
        env++;
    }
    return 0;
}

char **sort_env(char **env) 
{
    int i, j;
    char *temp;

    for (i = 0; env[i] != NULL; i++) {
        for (j = i + 1; env[j] != NULL; j++) 
        {
            char *var_name_i = env[i];
            char *var_name_j = env[j];
            if (ft_strcmp(var_name_i, var_name_j) > 0) 
            {
                temp = env[i];
                env[i] = env[j];
                env[j] = temp;
            }
        }
    }
    env[j] = NULL;
    return(env);
}

int minishell_export(char **args, char **env) 
{
    env = sort_env(env);
    while (*env != NULL) 
    {
        ft_printf("%s\n", *env);
        env++;
    }
    if (args[1] != NULL) {
        char *var_name = args[1];
        char *var_value = strchr(var_name, '=');
        
        if (var_value != NULL) {
            *var_value = '\0';
            var_value++;

            if (setenv(var_name, var_value, 1) != 0) {
                perror("setenv");
            }
        } else {
            fprintf(stderr, "Invalid format. Use: export VAR_NAME=VAR_VALUE\n");
        }
    } 
    else 
    {
        while (*env != NULL) 
        {
            ft_printf("%s\n", *env);
            env++;
        }

    }

    return 0;
}

int     ft_builtins(t_minishell *shell)
{
    // Verifica se o comando é "exit" para sair do shell
    if (ft_strcmp(shell->args[0], "exit") == 0) 
    {
        minishell_exit(shell->args);
        free(shell->init_str);
        return (0);
    }

    if(ft_strcmp(shell->args[0], "pwd") == 0)
    {
        minishell_pwd(shell->args);
        free(shell->init_str);
        return (0);
    }

    if(ft_strcmp(shell->args[0], "echo") == 0)
    {
        minishell_echo(shell->args);
        free(shell->init_str);
        return (0);
    }

    if(ft_strcmp(shell->args[0], "cd") == 0)
    {
        minishell_cd(shell->args);
        free(shell->init_str);
        return (0);
    }
    if(ft_strcmp(shell->args[0], "env") == 0)
    {
        minishell_env(shell->env);
        free(shell->init_str);
        return (0);
    }
    if(ft_strcmp(shell->args[0], "export") == 0)
    {
        minishell_export(shell->args, shell->env);
        free(shell->init_str);
        return(0);
    }
    return (1);
}