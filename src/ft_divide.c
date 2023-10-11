/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:04:08 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 17:32:03 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void        init_vars(int *begin_position, int *end_position, char *str, char divider)
{
    *begin_position = 0;
    if (str[0] == divider)
        *begin_position = 1;
    *end_position = 0;
    if (str[ft_strlen(str) - 1] == divider)
        *end_position = 1;
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
    char **new_tabs;
    int i;
    int secondary_index;
    int new_tab_len;

    new_tab_len = (((int)(ft_tab_len(split_tabs)) * 2) - 1);
    new_tabs = (char **)malloc((new_tab_len + begin_position + end_position + 1)*sizeof(char *));
    if (!new_tabs)
        exit_error("Malloc error\n");
    i = 0;
    secondary_index = 0;
    if (begin_position)
        new_tabs[i + secondary_index++] = ft_strdup(divider_string);
    while ((i + secondary_index) < (new_tab_len + end_position + begin_position))
    {
        new_tabs[i + secondary_index] = ft_strdup(split_tabs[i]);
        i++;
        if ((i + secondary_index) < (new_tab_len + end_position + begin_position))
        {
            new_tabs[i + secondary_index] = ft_strdup(divider_string);
            secondary_index++;
        }
    }
    new_tabs[i + secondary_index] = NULL;
    return(new_tabs);
}

char		**ft_divide(char *str, char divider)
{
    int begin_position;
    int end_position;
    char **split_tabs;
    char **new_tabs;

    init_vars(&begin_position, &end_position, str, divider);
    split_tabs = ft_split(str, divider);
    if (!split_tabs)
        exit_error("Malloc error!\n");
    new_tabs = get_divider_in(split_tabs, get_str_from_char(divider), begin_position, end_position);
    ft_free_tabs((void **)split_tabs);
    return(new_tabs);
}
