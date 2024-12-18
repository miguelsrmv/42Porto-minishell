/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/10/26 20:08:08 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define SQUOTE 39
# define DQUOTE 34
# define TRUE 1
# define FALSE 0

// Process Errors
# define MALLOC_ERROR "Error: Malloc error.\n"
# define WRITE_ERROR "Error: Write error.\n"
# define READ_ERROR "Error: Read error.\n"
# define CLOSE_ERROR "Error: Close error.\n"
# define PIPE_ERROR "Error: Pipe error.\n"
# define FORK_ERROR "Error: Fork error.\n"
# define ENV_ERROR "Error: Env error.\n"
# define DUP_ERROR "Error: Dup2 error.\n"
# define UNLINK_ERROR "Error: Unlink error.\n"
# define WAIT_ERROR "Error: Wait error.\n"
# define EOF_ERROR "exit\n"

// Usage errors
# define USAGE_ERROR "Usage error: \'./minishell\'.\n"
# define QUOTE_ERROR "Input error: unclosed quote\n"
# define SYNTAX_ERROR "Syntax error near unexpected token\n"
# define S_EOF "Syntax error: unexpected end of file\n"
# define EMPTY_ERROR "Ambiguous redirect\n"
# define COMMAND_ERROR ": command not found\n"
# define OPEN_ERROR ": No such file or directory\n"
# define DIRECTORY_ERROR ": Is a directory\n"
# define NOT_A_DIR_ERROR ": Not a directory\n"
# define DIR_OPEN_ERROR ": No such directory \n"
# define DIRECTORY_OUTPUT_ERROR ": Is a directory \n"
# define PERMISSION_ERROR ": Permission denied\n"
# define PERMISSION_IO_ERROR ": Permission denied \n"
# define EMPTY_INPUT_ERROR ""

// Exit code / signal errors
# define NO_SIGNAL 0
# define SIGINT_SIGNAL 130
# define SIGQUIT_SIGNAL 131
# define EOF_SIGNAL -1

extern int					g_status_flag;

enum						e_QuoteType
{
	OUT_QUOTE,
	IN_QUOTE,
	IN_DQUOTE
};

enum						e_PipeType
{
	OUT_PIPE,
	IN_PIPE
};

enum						e_TokenType
{
	SEPARATOR,
	REDIRECT,
	STRING,
	REDIRECT_TARGET
};

enum						e_CommandType
{
	NULL_COMMANDTYPE,
	NO_NULL_COMMANDTYPE,
	EXECUTABLE,
	BUILTIN,
	PERMISSION,
	DIRECTORY,
	NULL_DIRECTORY,
	NOT_A_DIRECTORY,
	NO_EXEC_INVALID_INPUT
};

enum						e_RedirectType
{
	NULL_REDIRECT,
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC,
	PIPE,
	INVALID,
};

enum						e_ValidType
{
	VALID,
	INVALID_INPUT,
	NONEXISTENT_INPUT,
	INVALID_INPUT_REDIR,
	INVALID_INPUT_READ,
	INVALID_OUTPUT_REDIR,
	INVALID_OUTPUT,
	INVALID_OUTPUT_WRITE,
	INVALID_CMD,
	EMPTY,
};

enum						e_BuiltinType
{
	EXPORT,
	CD
};

enum						e_ExpandType
{
	PID,
	EXIT_STATUS,
	NUMBER,
	ATSIGN,
	HASHTAG
};

// Structs
typedef struct s_token
{
	char					*token;
	int						type;
	struct s_token			*next;
}							t_token;

typedef struct s_command_table
{
	char					**cmd;
	char					*cmd_target;
	enum e_CommandType		command_type;
	void					*builtin_pointer;
	char					**cmd_before_expansion;

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
	int						current_g_status;
	bool					valid_command;
	struct s_command_table	*next;

}							t_command_table;

typedef struct s_memptr
{
	t_token					**lexer_list;
	t_command_table			**command_table;
	t_command_table			**first_node;
	char					**path_list;
	int						**pipe_fd;
	char					**argv;
	int						argc;
	char					**envp;
	int						return_value;
	char					*my_pwd;
	char					*my_oldpwd;
	int						unset_pwd_flag;
}							t_memptr;

// Function definitions
/// main.c
t_memptr					initialize_memptr(t_token **lexer_list,
								t_command_table **command_table, char **argv,
								char **envp);

/// bash_main.c
void						bash_main(t_memptr *memptr);
void						populate_from_environment(t_memptr *memptr);
void						bash_run(char **envp, t_memptr *memptr);

/// path_update.c

void						update_path(t_memptr *memptr);
void						clean_memory_but_path(t_memptr *memptr);

/// shell_update.c
void						update_shell_level(char ***envp, t_memptr *memptr);
void						replace_shell_level(char **envp, t_memptr *memptr,
								long level);
void						add_shell_level(char ***envp, t_memptr *memptr);

/// clean_memory.c
void						clear_lexer_list(t_token **lst);
void						clear_command_table(t_command_table **lst);
void						close_pipes_error(int **pipe);
void						clean_memory(t_memptr *memptr);
void						final_clear_and_exit(t_memptr memptr, char **envp,
								int **pipe_fd, t_command_table *current);

/// clean_memory_heredoc.c
void						clear_command_table_heredoc(t_command_table **lst);
void						clean_memory_heredoc(t_memptr *memptr);

/// clean_memory_pipes.c
void						clean_input(char *input, t_memptr memptr);

/// exit_error.c
void						exit_error(char *error, t_memptr memptr,
								char *extra_error);
void						non_exit_error(char *error, t_memptr memptr,
								char *extra_error);
void						set_g_status_flag(char *error);
void						print_to_fd(int fd, char *error, char *extra_error,
								t_memptr memptr);

/// get_input.c
void						trim_left_whitespace(char **input, t_memptr memptr);
void						update_input(char **input, t_memptr memptr);
char						*get_input(char *prompt, t_memptr memptr);
char						*get_input_2(char *prompt, t_memptr memptr);
bool						iscommandempty(const char *cmd, t_memptr memptr);

/// input_checker.c
int							check_in_quote(char *input);
int							check_in_pipe(char *input);

/// lexer.c
void						fill_in_list(char *input, t_token **head,
								t_memptr memptr);
t_token						*read_readline(t_memptr memptr);

/// lexer_linked_list.c
t_token						*create_token(char *token, int type,
								t_memptr memptr);
t_token						*last_token(t_token *list);
void						add_token_end(t_token **list, t_token *new);

/// lexer_get_tokens.c
int							is_valid_bash_char(char c);
char						*get_pipe_token(char *input, int *start, int *end);
char						*get_string_token(char *input, int *start,
								int *end);
void						advance_until_unquoted_whitespace(char *input,
								int *end, char quote_status);
char						*get_redirect_token(char *input, int *start,
								int *end);

/// fork_input.c
void						pipe_child(int *pipe_fd);
void						pipe_parent(char **input, int *pipe_fd,
								t_memptr memptr);
void						read_extra_input(int read_fd, char **input,
								t_memptr memptr);

/// parser.c
int							check_syntax(t_token *lexer_list);
int							count_cmds(t_token *current);
void						set_cmd(t_token *lexer_sublist,
								t_command_table **command_table,
								t_memptr memptr);
void						create_command_table(t_token *lexer_list,
								t_command_table **command_table,
								t_memptr memptr);
t_command_table				*parse_list(t_token *lexer_list, t_memptr memptr);

/// parser_set_redirs.c
void						fill_subarray(char **array, t_token *current, int i,
								t_memptr memptr);
int							count_redirect_targets(t_token *lexer_sublist);
void						fill_full_redir(t_token *current,
								t_command_table **command_table,
								t_memptr memptr);
void						init_command_table(t_command_table **cmd_table,
								int total_redir, t_memptr memptr);
void						set_full_redirections(t_token *lexer_sublist,
								t_command_table **command_table,
								t_memptr memptr);

/// parser_heredoc.c
void						check_heredocs(t_command_table **command_table,
								t_memptr memptr);
void						analyze_delimiter(char *unquoted_delimiter,
								char *delimiter, enum e_QuoteType *quote_status,
								t_memptr memptr);
void						create_heredoc_buffer(char *delimiter,
								t_command_table **command_table,
								enum e_QuoteType quote_status, t_memptr memptr);
void						create_heredoc(t_command_table **command_table,
								char *buffer, t_memptr memptr);

/// parser_heredoc_child.c
void						heredoc_child(char *delimiter, int *pipe_fd);
void						expand_buffer(char **buffer, t_memptr memptr,
								enum e_QuoteType quote_status);
void						clean_heredoc_child(t_memptr memptr,
								t_command_table **command_table);

/// parser_heredoc_parent.c
void						heredoc_parent(char **buffer, int *pipe_fd,
								t_memptr memptr, enum e_QuoteType quote_status);
int							read_from_pipe(int read_fd, char **buffer,
								t_memptr memptr, enum e_QuoteType quote_status);

/// clean_heredocs.c
void						clean_heredoc_buffers(t_command_table **cmd_table);

/// expander.c
int							is_valid_env_char(char c);
void						define_quote_flag(char c, int *pos,
								char *quote_flag);
void						expand_double_vector(char **vector,
								t_memptr memptr);
void						expand_command_table(t_command_table **cmd_table,
								t_memptr memptr);

/// expander_noquotes.c
void						normal_expansion(char **string, int *pos,
								char *quote_flag, t_memptr memptr);
void						ansi_quoting(char **string, int *start,
								t_memptr memptr);
void						expand_env_no_quotes(char **string, int *start,
								t_memptr memptr);
void						exit_value_expand(char **string, int *start,
								t_memptr memptr);
void						localization(char **string, int *start,
								t_memptr memptr);

/// expander_squote.c
void						squote_expansion(char **string, int *pos,
								char *quote_flag, t_memptr memptr);
void						take_out_outer_squotes(char **string, int *start,
								char *quote_flag, t_memptr memptr);

/// expander_dquote.c
void						dquote_expansion(char **string, int *pos,
								char *quote_flag, t_memptr memptr);
void						expand_env_quotes(char **string, int *start,
								int *end, t_memptr memptr);
void						expand_to_dollar_sign(char **string, int *start,
								t_memptr memptr);
int							take_out_outer_dquotes(char **string, int *start,
								t_memptr memptr);
void						exit_value_expand_quotes(char **string, int *start,
								int *end, t_memptr memptr);

/// expander_concatenate.c
int							concatenate(char **string, char *expanded_string,
								int *start, int end);
int							free_concatenate(char *left, char *right,
								char *temp, char *stringcpy);

/// executer_prepare_processes.c
int							**create_pipes(int process_num, t_memptr *memptr);
void						close_pipes(int **pipe_fd, t_command_table *current,
								t_memptr memptr);
void						close_remaining_pipes(int **pipe_fd,
								t_command_table *current, t_memptr memptr);
int							count_processes(t_command_table **command_table);
void						prepare_processes(t_command_table **command_table,
								char **envp, t_memptr *memptr);

/// executer_redir_checker.c
enum e_RedirectType			redir_check(char *redir_str);

/// executer_redir_setter.c
enum e_ValidType			set_redirs(int **pipe_fd, t_command_table **command,
								t_memptr memptr);
void						set_input_redir(int **pipe_fd,
								t_command_table **command, t_memptr memptr);
void						set_output_redir(int **pipe_fd,
								t_command_table **command, t_memptr memptr);
void						close_redir_pipes(int **pipe_fd,
								t_command_table **command, t_memptr memptr);
void						close_parent_pipes(int **pipe_fd, int process_num,
								t_memptr memptr);

/// executer_executable_checker.c
void						check_executables(t_command_table *current,
								char **path_list, t_memptr memptr);
void						absolute_check_executables(t_command_table *current,
								t_memptr memptr);
void						current_check_executables(t_command_table *current,
								t_memptr memptr);
void						relative_check_executables(t_command_table *current,
								char **path_list, t_memptr memptr);
void						check_executables_subfunc(t_command_table *current,
								char *test_command);

/// executer_dir_checker.c
void						check_directory_subfunc(t_command_table *current,
								char *test_command, t_memptr memptr);

/// executer_get_path.c
char						**get_path_list(t_memptr *memptr);
void						fill_in_result_from_path_list(char **path_list,
								char **result, t_memptr memptr);

/// executer_childparent_processes.c
void						process_parent(int **pipe_fd, int process_num,
								int *pid_array, t_memptr *memptr);
void						process_child(int **pipe_fd,
								t_command_table *current, char **envp,
								t_memptr memptr);
void						process_forks(t_command_table **command_table,
								char **envp, int process_num, t_memptr memptr);
void						create_pid_array(int **pid_array, int process_num,
								t_memptr memptr);
void						process_fork_subfunc(int *pid_array,
								t_command_table *current, int i);

/// executer_single_builtin.c
int							execute_single_builtin(t_command_table *current,
								char **envp, t_memptr *memptr);
int							execute_builtin(t_command_table *current,
								char **envp, t_memptr *memptr);
void						close_exit_fds(int original_stdin,
								int original_stdout);

/// executer_process_check.c
void						process_check(t_command_table **command_table,
								char **envp, t_memptr *memptr);
char						**get_path(char **envp, t_memptr *memptr);
int							check_path(char **envp);

/// executer_input_check.c
bool						input_check(t_command_table **command,
								t_memptr *memptr);
enum e_ValidType			check_input(t_command_table **command);
enum e_ValidType			input_target_check(char *target);

/// executer_output_check.c
bool						output_check(t_command_table **command,
								t_memptr *memptr);
enum e_ValidType			check_output(t_command_table **command,
								t_memptr memptr);
enum e_ValidType			output_target_check(char *target);
void						create_output(enum e_RedirectType input_type,
								char *target, t_memptr memptr);

/// executer_command_check.c
bool						command_check(t_command_table **command,
								char **path, t_memptr *memptr);
void						check_builtin(t_command_table *current);
void						remove_null_strings(t_command_table *current,
								t_memptr memptr);

/// final_nullstrings.c
char						**final_nullstrings(t_command_table *current,
								t_memptr memptr);
int							get_final_len(char **cmd_before_expansion,
								char **cmd);
void						fill_with_nonnullstrings(char **final_cmd,
								char **cmd_before_expansion, char **cmd,
								t_memptr memptr);
bool						is_string_truly_null(char *string_before_expansion,
								char *string_after_expansion);

/// signals.c
void						set_signal(void);
void						set_signal_during_processes_child(void);
void						set_signal_during_processes_parent(void);

/// signals_handler.c
void						sigint_handler(int signum);
void						sigint_handler_child(int signum);
void						sigquit_handler_child(int signum);
void						sigpipe_handler(int signum);
void						sigint_handler_during_processes_child(int signum);

/// signals_handler_input.c
void						set_signal_inputs_child(void);
void						set_signal_inputs_parent(void);
void						sigint_handler_inputs(int pipe_fd);

// Builtins
/// env.c
int							env(char **argv, char **envp);

/// export.c
void						print_export(char **envp, t_memptr *memptr);
bool						export_is_invalid(char *argument);
void						add_to_export_list(char *argument, char **envp,
								t_memptr *memptr);
int							export(char **argv, char **envp,
								t_command_table *current, t_memptr *memptr);

/// unset.c
int							unset(char **argv, char **envp,
								t_command_table *current, t_memptr *memptr);

/// cd.c

int							update_locations(char *old_dir, char *new_dir,
								t_memptr *memptr);
int							attempt_to_change_dir(char *path, t_memptr *memptr);
void						go_home(t_memptr *memptr);
void						go_oldpwd(t_memptr *memptr, int oldpwd_position);
int							cd(char **argv, char **envp,
								t_command_table *current, t_memptr *memptr);

/// pwd.c
int							pwd(char **argv);

/// echo.c
bool						check_newline_flag(char *flag);
int							echo(char **args);

/// exit.c
int							ft_exit(char **args, char **envp,
								t_command_table *current, t_memptr *memptr);

/// builtin_helpers.c
bool						argument_is_invalid(char *argument);
int							builtin_argument_checker(char **argv);
void						error_message(char *message, int new_status_flag);

// environment_getters_setters.c

void						check_pwd_edge_case(char **envp, char *key,
								char *value, t_memptr *memptr);
void						add_env_value(char **envp, char *key, char *value,
								t_memptr *memptr);
void						set_env_value(char **envp, char *key, char *value,
								t_memptr *memptr);
void						set_env_value_cd(char **envp, char *key,
								char *value, t_memptr *memptr);
void						remove_env_value(char **envp, char *key,
								t_memptr *memptr);

// environment_helpers.c
void						cpy_old_vars_skip_position(char **old, char **dest,
								int index_to_skip);

int							find_env_var(char **envp, char *key);

char						*get_env_value(char **envp, char *key,
								t_memptr *memptr);

// environment_key_values.c
char						*new_key_value(char *key, char *value,
								t_memptr *memptr);
char						*new_key(char *key, t_memptr *memptr);

// sort_envp.c
void						bubble_sort(char **envp);
void						swap(char **a, char **b);

#endif
