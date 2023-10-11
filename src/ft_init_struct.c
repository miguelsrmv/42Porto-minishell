#include "minishell.h"

void    ft_init_struct(t_minishell *shell)
{
    shell->init_str = NULL;
    shell->expanded_str = NULL;
    shell->command = NULL;
    shell->args = NULL;
    shell->joined_path = NULL;
    shell->fd_input = -1; // Valor padrão para um descritor de arquivo inválido
    shell->fd_output = -1; // Valor padrão para um descritor de arquivo inválido
    shell->pwd = NULL;
}