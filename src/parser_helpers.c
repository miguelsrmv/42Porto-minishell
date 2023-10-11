/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:23:06 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 14:02:24 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_redirect(char *token)
{
    int tok_len;

    tok_len = ft_strlen(token);
    if (tok_len == 1)
    {
        if (!ft_strncmp(token, "<", 1) || !ft_strncmp(token, ">", 1))
            return (IS_REDIRECT);
    }
    if (tok_len == 2)
    {
        if (!ft_strncmp(token, "<<", 2) || !ft_strncmp(token, ">>", 2)
        || !ft_strncmp(token, "<>", 2))
            return (IS_REDIRECT);
    }
    return (NOT_REDIRECT);
}

void        ft_jointabs(char **lexer, int i, int tab_len)
{
    char *temp;

    temp = lexer[i];
    lexer[i] = ft_strjoin(lexer[i], lexer[i + 1]);
    free(temp);
    i++;
    while (i < tab_len)
    {
        lexer[i] = lexer [i + 1];
        i++;
    }
    free(lexer[i]);
}


char    **byte_by_byte_tab(char **tabs, int tab_len, char c)
{
    
}


/*
 char **ft_split_tab(char **tabs, int str_index, int tab_len, char c)
 {
    char **splitted_tab;
    char **new_tab;
    int tab_index;
    int secondary_index;

    splitted_tab = ft_split(tabs[str_index], c);
    new_tab = (char **)malloc((tab_len + (-1 + ft_tab_len(splitted_tab) * 2)) * sizeof(char *));
    if (!splitted_tab || !new_tab)
        exit_error("Trouble Mallocing");
    tab_index = 0;
    while (tab_index < str_index)
    {
        new_tab[tab_index] = ft_strdup(tabs[tab_index]);
        tab_index++;
    }
    secondary_index = 0;
    while (splitted_tab[secondary_index])
    {
        if ((ft_strchr(tabs[str_index], c) == tabs[str_index]))
        {
            new_tab[tab_index + secondary_index] = ft_strdup("|");
            tab_index++;
        }
        new_tab[tab_index + secondary_index] = ft_strdup(splitted_tab[secondary_index]);
        secondary_index++;
        if (splitted_tab[secondary_index])
        {
            new_tab[tab_index + secondary_index] = ft_strdup("|");
            tab_index++;
        }
    }
    while (tabs[tab_index])
    {
        new_tab[tab_index + secondary_index] = ft_strdup(tabs[tab_index]);
        tab_index++;
    }
    ft_free_tabs((void **)tabs);
    return (new_tab);

*/    
/*
    while (tab_index < (tab_len + 1))
    {
        new_tab[tab_index] = (char *)malloc(10 * sizeof(char));
        tab_index++;
    }
    tab_index = 0;
    while (&tabs[tab_index] != &position)
    {
        (*new_tab)[tab_index] = (*tabs)[tab_index];
        tab_index++;
    }
    *new_tab[tab_index] = '\0';
    tab_index++;
    while (tab_index < tab_len)
    {
        (*new_tab)[tab_index] = (*tabs)[tab_index - 1];
        tab_index++;
    }
    ft_free_tabs((void **)tabs);
    return(new_tab);
*/
 