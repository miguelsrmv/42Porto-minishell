/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/17 11:32:16 by mde-sa--         ###   ########.fr       */
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
# include <fcntl.h>

# define OUT_QUOTE 0
# define IN_QUOTE 1
# define IN_DQUOTE 2

# define NOT_REDIRECT 0
# define IS_REDIRECT 1

# define VALID 0
# define INVALID 1

// Structs

typedef struct s_command {
	char	*cmd;
	char	*path;
	char	**args;
}	t_command;

/*Lidar com multiplos ??? */
typedef struct s_IO_redirection {
	int	in;
	int	out;
	int	err;
}	t_io_redir;

typedef struct s_command_table {
	t_command			**cmd_array;
	t_io_redir			**io_redir;
	int					cmd_num;
}	t_command_table;

typedef struct s_token {
	char			*token;
	struct s_token	*next;
}	t_token;

// Function definitions

/// Main.c
void	exit_error(char *error_message);
void	free_list(t_token *head);

/// get_input.c
int		check_in_quote(char *input);
char	*get_input(char *prompt);
char	*check_valid_input(char *input);

/// lexer.c
void	fill_in_list(char *input, t_token **head);
t_token	*read_readline(void);

/// Linked List Functions
t_token	*create_token(char *string);
t_token	*last_token(t_token *list);
void	add_token_end(t_token **list, t_token *new);

/// lexer_get_tokens.c
int		is_valid_bash_char(char c);
char	*get_pipe_token(char *input, int *start, int *end);
char	*get_string_token(char *input, int *start, int *end);
char	*get_redirect_token(char *input, int *start, int *end);
char	*get_quote_token(char *input, int *start, int *end);

#endif