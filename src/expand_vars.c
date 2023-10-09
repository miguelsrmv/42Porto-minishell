/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:36:01 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/09 15:00:07 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_env_var(char *string)
{
    int i;
    char *env_var;

    i = 1;
    while (string[i] != ' ')
        i++;
    env_var = (char *)malloc((i * sizeof(char)) + 1);
    if (!env_var)
        return (NULL);                                      // EXIT ERROR
    i = 0;
    while (string[i + 1] != ' ')
    {
        env_var[i] = string[i + 1];
        i++;
    }
    env_var[i] = '\0';
    return(env_var);
}

void update_len_environmentvar(int *len, char *string)
{
    char    *env_var;
   // char    *new_var;

    env_var = get_env_var(string);
   // new_var = get_expanded_env_var(env_var);
    len = len - ft_strlen(env_var); //+ ft_strlen(new_var);
    free(env_var);
   // free(new_var);
}

char *expand_vars(char *string)
{
    int len;
    int i;


   // if (!ft_strchr(string, '$'))
   //     return (string);
    len = ft_strlen(string);
    i = 0;
    while (string[i])
    {
        if ((string[i] == ' ' || i == 0) && (string[i + 1] == '\''))
        {
            i++;
            while (!((string[i] == '\'') && (string[i + 1] == '\0' || string[i + 1] == ' ')))
            {
                len++;
                i++;
            }
            if (string[i] == '$')
                update_len_environmentvar(&len, &string[i]);
            i++;
        }
        write(1, &string[i], 1);
        i++;
    }
    return ("");
}


