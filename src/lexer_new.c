/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:52:58 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/13 22:06:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pipe_token(char *input, int *start, int *end)
{
	*end = *start;
	*end++;
	return (ft_strndup(input[*start]), end - start);
}

char	*get_string_token(char *input, int *start, int *end)
{
	*end = *start;
	while (input[*end] && ft_isalnum(input[*end]))
		(*end)++;
	return (ft_strndup(input[*start]), end - start);
}

char	*get_redirect_token(char *input, int *start, int *end)
{
	char	*temp_result;
	char	**splitted_array;
	char	*result;

	*end = (*start) + 1;
	if (input[(*end)] == '>' || input[(*end)] == '<')
		(*end)++;
	while (ft_isspace(input[*end]))
		(*end)++;
	while (ft_isalnum(input[*end]))
		(*end)++;
	temp_result = ft_strndup(input[*start], end - start);
	splitted_array = ft_split(temp_result, ' ');
	result = ft_strjoin(splitted_array[0], splitted_array[1]);
	free(temp_result);
	ft_free_tabs((void **)splitted_array);
	return (result);
}

void	fill_in_list(char *input, t_token **head, int start, int end)
{	
	while (input[start])
	{
	/*	if ((end == 0 && ft_isquote(input[1])) || (input[end + 1] && ft_isspace(input[end]) && ft_isquote(input[end + 1])))
			add_token_end(head, create_token(get_quote_token(input, &start, &end)));*/
		while(ft_isspace(input[start]))
			start++;
		if (ft_isalnum(input[start]))
			add_token_end(head, create_token
				(get_string_token(input, &start, &end)));
		else if (input[start] == '<' || input[start] == '>')
			add_token_end(head, create_token
				(get_redirect_token(input, &start, &end)));
		else if (input[start] == '|')
			add_token_end(head, create_token
				(get_pipe_token(input, &start, &end)));
		start = end;
	}
}

t_token	*read_readline(char *input)
{
	t_token	*head;
	int		start;
	int		end;

	head = create_token(input);
	start = 0;
	end = 0;
	fill_in_list(input, &head, start, end);
	return (head);
}
