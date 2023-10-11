/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:32:18 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 14:35:02 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    separate_pipes(char **lexer, int i)
{
    char **newdivision;
    if (!ft_strchr(lexer[i], '|'))
        return ;
    newdivision = ft_divide(lexer[i], '|');
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
        separate_pipes(lexer, i);
        i++;
    }
    return (1);
}
