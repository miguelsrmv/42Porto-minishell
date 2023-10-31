/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:48:14 by bmota-si          #+#    #+#             */
/*   Updated: 2023/10/31 18:22:11 by bmota-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    put_quotes(char **tab, char c)
{
    char 
}

int     str_env_len(char **env)
{
    int     i;
    
    i = 0;
    while(env[i])
        i++;
    return (i);
}

void    sort_env(char **tab, int env_len)
{
    int     ordered;
    int     i;
    char    *tmp;

    ordered = 0;
    while(tab && ordered == 0)
    {
        ordered = 1;
        i = 0;
        while(i < env_len - 1)
        {
            if(ft_strcmp(tab[i], tab[i + 1]) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                ordered = 0;
            }
            i++;
        }
        env_len--;
    }
}

void    print_sorted_env(char **new_env)
{
    int     i;
    
    sort_env(new_env, str_env_len(new_env));
    put_quotes(new_env, '=');
    i = 0;
    while (new_env[i])
    {
        ft_printf("declare -x %s\n", new_env[i]);
        i++;
    }
}

int     minishell_export(t_minishell *shell)
{
    int new_env;
    int error_ret;

    new_env = 0;
    if(!shell->args[1])
    {
        print_sorted_env(shell->new_env);
        return(0);
    }
    else
        return (1);
}