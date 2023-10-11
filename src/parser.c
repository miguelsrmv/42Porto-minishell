/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:32:18 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 17:56:45 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void separate_pipes(char **lexer, int i, int tab_len)
{
    char **newdivision;
    char **new_lexer;
    int main_index;
    int secondary_index;

    if (!ft_strchr(lexer[i], '|'))
        return ;
    newdivision = ft_divide(lexer[i], '|');
    main_index = 0;
    secondary_index = 0;
    new_lexer = (char **)malloc((tab_len + ft_tab_len(newdivision))* (sizeof(char *)));
    while (main_index < i)
    {
        new_lexer[main_index] = ft_strdup(lexer[main_index]);
        main_index++;
    }
    while (newdivision[secondary_index] != NULL)
    {
        new_lexer[main_index + secondary_index] = ft_strdup(newdivision[secondary_index]);
        secondary_index++;
    }
    while (main_index < tab_len - 1)
    {
        new_lexer[main_index + secondary_index] = ft_strdup(lexer[main_index + 1]);
        main_index++;
    }
    new_lexer[main_index + secondary_index] = NULL;
    ft_free_tabs((void **)lexer);
}


int parser(char **lexer, int tab_len)
{
    int i;

    i = 0;
    while (lexer[i])
    {
        if (ft_is_redirect(lexer[i]) == IS_REDIRECT)
        {
            if (i == tab_len)
                exit_error("Redirection malpositioned");
            ft_jointabs(lexer, i, tab_len);
            i--;
        }
        i++;
    }
    i = 0;
    while (lexer[i])
    {
        separate_pipes(lexer, i, tab_len);
        i++;
    }
    return (1);
}
