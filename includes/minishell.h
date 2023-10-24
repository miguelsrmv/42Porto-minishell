/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/24 18:19:44 by mde-sa--         ###   ########.fr       */
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

enum e_QuoteType {
	OUT_QUOTE,
	IN_QUOTE,
	IN_DQUOTE
};

enum e_TokenType {
	PIPE,
	REDIRECT,
	STRING,
	REDIRECT_TARGET
};

# define VALID 0
# define INVALID 1

// Structs
typedef struct s_token {
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_command_table {
	char					**cmd;
	char					**full_input;
	char					**full_output;
	char					*input_type;
	char					*output_type;
	char					*input_file;
	char					*output_file;
	struct s_command_table	*next;
}	t_command_table;

typedef struct s_error {
	t_token			*lexer_list;
	t_command_table	*command_table;
}	t_error;

// Function definitions

/// Helper functions
void			exit_error(char *error_message, t_error error);
void			print_lexer_tokens(t_token *head);
void			print_command_table(t_command_table *command_table);

/// Main.c
void			free_list(t_token *head);

/// get_input.c
int				check_in_quote(char *input);
char			*get_input(char *prompt);
char			*check_valid_input(char *input);

/// lexer.c
void			fill_in_list(char *input, t_token **head);
t_token			*read_readline(t_error error);

/// Linked List Functions
t_token			*create_token(char *string, int type);
t_token			*last_token(t_token *list);
void			add_token_end(t_token **list, t_token *new);
void			clear_lexer_list(t_token **lst);
void			clear_command_table(t_command_table **lst);



/// lexer_get_tokens.c
int				is_valid_bash_char(char c);
char			*get_pipe_token(char *input, int *start, int *end);
char			*get_string_token(char *input, int *start, int *end);
char			*get_redirect_token(char *input, int *start, int *end);
char			*get_quote_token(char *input, int *start, int *end);

/// parser.c
int				check_syntax(t_token *lexer_list);
void			set_cmd(t_token *lexer_sublist,
					t_command_table **command_table, t_error error);	
void			create_command_table(t_token *lexer_list,
					t_command_table **command_table, t_error error);
t_command_table	*parse_list(t_token *lexer_list, t_error error);

/// parser_redirs.c
void			fill_array(char **array, t_token *current,
					t_command_table **command_table, int i);
void			set_final_redirection(t_command_table **command_table,
					t_error error);
int				count_redirect_targets(t_token *lexer_sublist);
void			set_full_redirections(t_token *lexer_sublist,
					t_command_table **command_table, t_error error);

/// expander.c
void			expand_command_table(t_command_table **command_table);
void			expand_double_vector(t_command_table **command_table,
					char **vector);
char			*expand_env(char *string);
char			*concatenate_env_substrings(char *left, char *env,
					char *right, char *string);
int				is_valid_env_char(char c);

#endif