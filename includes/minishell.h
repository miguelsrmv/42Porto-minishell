/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/13 21:36:01 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"
# include <unistd.h>
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define OUT_QUOTE 0
# define IN_QUOTE 1

// Structs
typedef struct s_split_numbers {
	int		word_count;
	int		in_word;
	int		in_quote;
	char	quote_char;
	size_t	i;
}	t_split_numbers;

typedef struct s_env {
	char	*env_var;
	char	*expanded_var;
	int		env_var_len;
	int		expanded_var_len;
}	t_env;

typedef struct s_token {
	char			*token;
	struct s_token	*next;
}	t_token;

// Function definitions
/// Linked List Functions
t_token *create_token(char *string);
t_token *last_token(t_token *list);
void	add_token_end(t_token **list, t_token *new);


/// lexer.c
char	**readline_split(const char *s);

/// lexer_new.c
t_token	*read_readline(char *input);

#endif