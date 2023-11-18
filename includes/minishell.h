/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/18 18:34:09 by mde-sa--         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

# define squote '\''
# define dquote '\"'

enum e_QuoteType {
	OUT_QUOTE,
	IN_QUOTE,
	IN_DQUOTE
};

enum e_TokenType {
	SEPARATOR,
	REDIRECT,
	STRING,
	REDIRECT_TARGET
};

enum e_CommandType {
	EXECUTABLE,
	BUILTIN
};

enum e_RedirectType {
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC,
	PIPE,
	NONE,
	INVALID
};

enum e_ValidType {
	VALID,
	INVALID_INPUT,
	INVALID_INPUT_REDIR,
	INVALID_OUTPUT_REDIR,
	INVALID_CMD
};

// Structs
typedef struct s_token {
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_command_table {
	char					**cmd;
	char					*cmd_target;
	enum e_CommandType		command_type;

	char					**full_input;
	char					*input_target;
	enum e_RedirectType		input_type;
	int						input_fd;

	char					**full_output;
	char					*output_target;
	enum e_RedirectType		output_type;
	int						output_fd;

	int						pid;
	int						command_no;
	struct s_command_table	*next;
}	t_command_table;

typedef struct s_error {
	t_token			*lexer_list;
	t_command_table	*command_table;
}	t_error;


// Function definitions
/// Helper functions
void				exit_error(char *error_message, t_error error);
void				print_lexer_tokens(t_token *head);
void				print_command_table(t_command_table *command_table);

/// main.c
void				free_list(t_token *head);

/// get_input.c
int					check_in_quote(char *input);
char				*get_input(char *prompt);
char				*check_valid_input(char *input);

/// lexer.c
void				fill_in_list(char *input, t_token **head);
t_token				*read_readline(t_error error);

/// lexer_linked_list.c
t_token				*create_token(char *string, int type);
t_token				*last_token(t_token *list);
void				add_token_end(t_token **list, t_token *new);
void				clear_lexer_list(t_token **lst);
void				clear_command_table(t_command_table **lst);

/// lexer_get_tokens.c
int					is_valid_bash_char(char c);
char				*get_pipe_token(char *input, int *start, int *end);
char				*get_string_token(char *input, int *start, int *end);
void				advance_until_unquoted_whitespace(char *input, int *end,
						char quote_status);
char				*get_redirect_token(char *input, int *start, int *end);

/// parser.c
int					check_syntax(t_token *lexer_list);
void				set_cmd(t_token *lexer_sublist,
						t_command_table **command_table, t_error error);	
void				create_command_table(t_token *lexer_list,
						t_command_table **command_table, t_error error);
t_command_table		*parse_list(t_token *lexer_list, t_error error);

/// parser_redirs.c
void				fill_array(char **array, t_token *current, int i);
int					count_redirect_targets(t_token *lexer_sublist);
void				fill_full_redir(t_token *current,
						t_command_table **command_table);
void				initialize_command_table(t_command_table **command_table);
void				set_full_redirections(t_token *lexer_sublist,
						t_command_table **command_table, t_error error);

/// expander_env.c
void				expand_command_table(t_command_table **command_table);
void				expand_double_vector(char **vector);
char				*concatenate_env_substrings(char *left, char *env,
						char *right, char *string);
int					is_valid_env_char(char c);
void				expand(char **string, int *start, char *quote_flag);


/// expander_contract.c
void				contract_double_vector(char **vector);
char				*take_out_quotes(char *string);

/// expander_subfunc.c
void				expand_to_dollar_sign(char **string, int *start);
void				expand_env_no_quotes(char **string, int *start);
void				expand_env_quotes(char **string, int *start,
						char *quote_flag);
void				take_out_after_quotes(char **string, int *start);
void				take_out_quote_flag(char **string, int *start);
void				concatenate(char **string, char *expanded_string,
						int *start, int end);


/// executer.c
int					count_processes(t_command_table **command_table);
int					**create_pipes(int **pipe_fd, int process_num);
t_command_table		*create_processes(t_command_table **current,
						int process_num);
void				prepare_processes(t_command_table **command_table,
						char **envp);

/// executer_input_checker.c
enum e_RedirectType	redir_check(char *redir_str);
enum e_ValidType	check_input(t_command_table **command);
enum e_ValidType	check_output(t_command_table **command);
void				set_redirections(int **pipe_fd, t_command_table **command);
void				check_redirections(int **pipe_fd,
						t_command_table **command);

/// executer_cmd_checker.c
void				check_commands(t_command_table **command_table,
						char **path_list);
char				**get_path_list(void);
int					check_builtin(char *command);

#endif