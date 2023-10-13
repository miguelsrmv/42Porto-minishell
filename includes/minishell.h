/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/13 21:36:01 by mde-sa--         ###   ########.fr       */
=======
/*   Updated: 2023/10/11 16:21:32 by mde-sa--         ###   ########.fr       */
>>>>>>> eb98c3690bb6cbebd7ea253ae5df8c25a40c2114
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

# define NOT_REDIRECT 0
# define IS_REDIRECT 1

// Structs
typedef struct s_token {
	int		token_count;
	int		in_token;
	int		in_quote;
	char	quote_char;
	size_t	i;
}	t_token;

typedef struct s_command {
	char	*cmd;
	char	*path;
	char	**args;
} t_command;

/*Lidar com multiplos ??? */
typedef struct s_IO_redirection {
	int	in; 
	int out; 
	int err;
} t_io_redir;

typedef struct s_command_table {
	t_command			**cmd_array;
	t_io_redir			**IO_redir;
	int					cmd_num;
} t_command_table;



typedef struct s_token {
	char			*token;
	struct s_token	*next;
}	t_token;

// Function definitions
<<<<<<< HEAD
/// Linked List Functions
t_token *create_token(char *string);
t_token *last_token(t_token *list);
void	add_token_end(t_token **list, t_token *new);

=======
void exit_error(char *error_message);
>>>>>>> eb98c3690bb6cbebd7ea253ae5df8c25a40c2114

/// lexer.c
char	**readline_split(const char *s);

<<<<<<< HEAD
/// lexer_new.c
t_token	*read_readline(char *input);
=======
// parser_helpers.c
int 	ft_is_redirect(char *token);
void    ft_jointabs(char **lexer, int i, int tab_len);
char 	**ft_split_tab(char **tabs, int str_index, int tab_len, char c);


// parser.c
void    	separate_pipes(char **lexer, int i, int tab_len);
int			parser(char **lexer, int tab_len);


char		**ft_divide(char *str, char divider);
char *ft_strndup(const char *src, size_t n);
int  ft_tab_len(char **tab);
>>>>>>> eb98c3690bb6cbebd7ea253ae5df8c25a40c2114

#endif