/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:04:08 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 15:22:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void        init_vars(int *begin_position, int *end_position, char *str, char divider)
{
    begin_position = 0;
    if (str[0] == divider)
        begin_position = 1;
    end_position = 0;
    if (str(ft_strlen(str) - 1) == divider)
        end_position = 1;
}

static int     char_counter(char *str, char divider)
{
    int i;
    int char_count;

    i = 0;
    char_count = 0;
    while (str[i])
    {
        if (str[i] == divider)
            char_count++;
        i++;
    }
    return (char_count);
}

static char *get_str_from_char(char divider)
{
    char *divider_string;
    
    divider_string = (char *)malloc(2*sizeof(char));
    if (!divider_string)
        exit_error("Malloc error!\n");
    divider_string[0] = divider;
    divider_string[1] = '\0';
    return(divider_string);
}

static char    **get_divider_in(char **split_tabs, char *divider_string, int begin_position, int end_position)
{
    int pipe_count;
    char **newtabs;
    int i;
    int secondary_index;

    newtabs = (char **)malloc(((ft_tab_len(split_tabs) * 2) - 1) + begin_position + end_position);
    if (!newtabs)
        exit_error("Malloc error\n");
    i = 0;
    secondary_index = 0;
    if (begin_position)
        newtabs[i++] = ft_strdup(divider_string);
    while (newtabs[i])
    {
        new_tabs[i] = ft_strdup(split_tabs[i]);
        i++;
        if (newtabs[i])
        {
            new_tabs[i] = ft_strdup(divider_string);
            i++;
        }
    }
    if (end_position)
        new_tabs[i] = ft_strdup(divider_string);
    return(newtabs);
}

char		**ft_divide(char *str, char divider)
{
    int begin_position;
    int end_position;
    char **split_tabs;
    char **newtabs;

    init_vars(*begin_position, *end_position, *str, divider);
    split_tabs = ft_split(str, divider);
    if (!split_tabs)
        exit_error("Malloc error!\n");
    newtabs = get_divider_in(split_tabs, get_str_from_char(divider), begin_position, end_position);
    free_tabs(split_tabs);
    return(newtabs);
}
