/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/11/26 17:51:17 by mde-sa--         ###   ########.fr       */
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

# define SQUOTE '\''
# define DQUOTE '\"'
# define USAGE_ERROR "Usage: \'./minishell\'."
# define MALLOC_ERROR "Malloc error."
# define SYNTAX_ERROR "Syntax error."
# define OPEN_ERROR "Open file error."
# define WRITE_ERROR "Write file error."
# define CLOSE_ERROR "Close file error."
# define TRUE 1
# define FALSE 0

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
	char					*heredoc_buffer;

	char					**full_output;
	char					*output_target;
	enum e_RedirectType		output_type;
	int						output_fd;

	int						pid;
	int						command_no;
	struct s_command_table	*next;
}	t_command_table;

typedef struct s_memptr {
	t_token			*lexer_list;
	t_command_table	*command_table;
}	t_memptr;


// Function definitions

/// Exit Error
void				clear_lexer_list(t_token **lst);
void				clear_command_table(t_command_table **lst);
void				exit_error(char *error_message, t_memptr memptr);

/// main.c
void				free_list(t_token *head);

/// get_input.c
int					check_in_quote(char *input);
char				*get_input(char *prompt);
char				*check_valid_input(char *input);

/// lexer.c
void				fill_in_list(char *input, t_token **head, t_memptr memptr);
t_token				*read_readline(t_memptr memptr);

/// lexer_linked_list.c
t_token				*create_token(char *token, int type, t_memptr memptr);
t_token				*last_token(t_token *list);
void				add_token_end(t_token **list, t_token *new);

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
						t_command_table **command_table, t_memptr memptr);	
void				create_command_table(t_token *lexer_list,
						t_command_table **command_table, t_memptr memptr);
t_command_table		*parse_list(t_token *lexer_list, t_memptr memptr);

/// parser_set_redirs.c
void				fill_subarray(char **array, t_token *current, int i);
int					count_redirect_targets(t_token *lexer_sublist);
void				fill_full_redir(t_token *current,
						t_command_table **command_table);
void				initialize_command_table(t_command_table **command_table,
						int total_redir, t_memptr memptr);
void				set_full_redirections(t_token *lexer_sublist,
						t_command_table **command_table, t_memptr memptr);

/// parser_heredoc.c
void				check_heredocs(t_command_table **command_table,
						t_memptr memptr);
void				create_heredoc_buffer(char *delimiter,
						char **buffer, t_memptr memptr);
void				create_heredoc_file(t_command_table **command_table,
						char *buffer, t_memptr memptr);

/// expander.c
int					is_valid_env_char(char c);
void				define_quote_flag(char c, int *pos, char *quote_flag);
void				expand_double_vector(char **vector);
void				expand_command_table(t_command_table **command_table);

/// expander_noquotes.c
void				normal_expansion(char **string, int *pos, char *quote_flag);
void				ansi_quoting(char **string, int *start, char *quote_flag);
void				expand_env_no_quotes(char **string, int *start,
						char *quote_flag);
void				take_out_after_quotes(char **string, int *start,
						char *quote_flag);

/// expander_squote.c
void				squote_expansion(char **string, int *pos, char *quote_flag);
void				take_out_outer_squotes(char **string, int *start,
						char *quote_flag);

/// expander_dquote.c
void				dquote_expansion(char **string, int *pos,
						char *quote_flag);
void				expand_env_quotes(char **string, int *start,
						char *quote_flag);
void				expand_to_dollar_sign(char **string, int *start,
						char *quote_flag);
int					take_out_outer_dquotes(char **string, int start);

/// expander_concatenate.c
void				concatenate(char **string, char *expanded_string,
						int *start, int end);
void				concatenate_for_dquote(char **string, char *expanded_string,
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

/// Helper functions
void				print_lexer_tokens(t_token *head);
void				print_command_table(t_command_table *command_table);

#endif