/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/01/19 14:52:06 by bmota-si         ###   ########.fr       */
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
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>
# include <signal.h>

# define SQUOTE '\''
# define DQUOTE '\"'
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
# define QUOTE_ERROR "Input error: unclosed quote.\n"
# define SYNTAX_ERROR "Syntax error near unexpected token.\n"
# define COMMAND_ERROR "command not found\n"
# define OPEN_ERROR "No such file or directory.\n"
# define DIRECTORY_ERROR "Is a directory\n"

// Exit code / signal errors
# define NO_SIGNAL 0
# define SIGINT_SIGNAL 130
# define EOF_SIGNAL -1

extern int	g_status_flag;

enum e_QuoteType {
	OUT_QUOTE,
	IN_QUOTE,
	IN_DQUOTE
};

enum e_PipeType {
	OUT_PIPE,
	IN_PIPE
};

enum e_TokenType {
	SEPARATOR,
	REDIRECT,
	STRING,
	REDIRECT_TARGET
};

enum e_CommandType {
	NULL_COMMANDTYPE,
	NO_NULL_COMMANDTYPE,
	EXECUTABLE,
	BUILTIN
};

enum e_RedirectType {
	NULL_REDIRECT,
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC,
	PIPE,
	INVALID
};

enum e_ValidType {
	VALID,
	INVALID_INPUT,
	NONEXISTENT_INPUT,
	INVALID_INPUT_REDIR,
	INVALID_OUTPUT_REDIR,
	INVALID_CMD
};

enum e_BuiltinType {
	EXPORT,
	CD
};

enum e_ExpandType {
	PID,
	EXIT_STATUS,
	NUMBER,
	ATSIGN,
	HASHTAG
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
	void					*builtin_pointer;

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
	t_token			**lexer_list;
	t_command_table	**command_table;
	char			**path_list;
	int				**pipe_fd;
	char			**argv;
	char			**envp;
	int				return_value;
}	t_memptr;

typedef struct s_env
{
	char	**envp;
	char	**env_var;
	char	*pwd;
	char	*oldpwd;
}			t_env;

typedef struct s_export
{
	int		i;
	int		j;
	char	*var;
}			t_export;

// Function definitions
/// Main.c
t_memptr			initialize_memptr(t_token **lexer_list,
						t_command_table **command_table,
							char **argv, char **envp);

/// Bash_main.c
void				bash_main(char **envp, t_memptr *memptr);
void				bash_run(char **envp, t_memptr *memptr);
t_env				*set_environment_vars(char **envp, t_memptr memptr);
void				update_envp(char ***envp, t_memptr *memptr, t_env *env_vars);

/// Exit Error
void				clear_lexer_list(t_token **lst);
void				clear_command_table(t_command_table **lst);
void				clean_memory(t_memptr memptr);
void				close_pipes_error(int **pipe);
void				exit_error(char *error_message, t_memptr memptr, ...);

/// get_input.c
void				trim_left_whitespace(char **input, t_memptr memptr);
void				update_input(char **input, t_memptr memptr);
char				*get_input(char *prompt, t_memptr memptr);

/// input_checker.c
int					check_in_quote(char *input);
int					check_in_pipe(char *input);
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
int					count_cmds(t_token *current);
void				set_cmd(t_token *lexer_sublist,
						t_command_table **command_table, t_memptr memptr);	
void				create_command_table(t_token *lexer_list,
						t_command_table **command_table, t_memptr memptr);
t_command_table		*parse_list(t_token *lexer_list, t_memptr memptr);

/// parser_set_redirs.c
void				fill_subarray(char **array, t_token *current, int i,
						t_memptr memptr);
int					count_redirect_targets(t_token *lexer_sublist);
void				fill_full_redir(t_token *current,
						t_command_table **command_table, t_memptr memptr);
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
void				expand_double_vector(char **vector, t_memptr memptr);
void				expand_command_table(t_command_table **command_table,
						t_memptr memptr);

/// expander_noquotes.c
void				normal_expansion(char **string, int *pos, char *quote_flag,
						t_memptr memptr);
void				ansi_quoting(char **string, int *start,	t_memptr memptr);
void				expand_env_no_quotes(char **string, int *start,
						t_memptr memptr);
void				exit_value_expand(char **string, int *start, t_memptr memptr);
void				localization(char **string, int *start,	t_memptr memptr);

/// expander_squote.c
void				squote_expansion(char **string, int *pos, char *quote_flag,
						t_memptr memptr);
void				take_out_outer_squotes(char **string, int *start,
						char *quote_flag, t_memptr memptr);

/// expander_dquote.c
void				dquote_expansion(char **string, int *pos, char *quote_flag,
						t_memptr memptr);
void				expand_env_quotes(char **string, int *start, int *end,
						t_memptr memptr);
void				expand_to_dollar_sign(char **string, int *start,
						t_memptr memptr);
int					take_out_outer_dquotes(char **string, int *start,
						t_memptr memptr);
void				exit_value_expand_quotes(char **string, int *start,
						int *end, t_memptr memptr);

/// expander_concatenate.c
int					concatenate(char **string, char *expanded_string,
						int *start, int end);
int					free_concatenate(char *left, char *right, char *temp,
						char *stringcpy);

/// executer_prepare_processes.c
int					**create_pipes(int **pipe_fd, int process_num,
						t_memptr *memptr);
t_command_table		*create_processes(t_command_table **current,
						int process_num);
void				close_pipes(int **pipe_fd, t_command_table *current,
						t_memptr memptr);
int					count_processes(t_command_table **command_table);
void				prepare_processes(t_command_table **command_table,
						char **envp, t_memptr *memptr);

/// executer_redir_checker.c
enum e_RedirectType	redir_check(char *redir_str);
enum e_ValidType	check_input(t_command_table **command);
enum e_ValidType	check_output(t_command_table **command);
enum e_ValidType	check_redirections(int **pipe_fd, t_command_table **command,
						t_memptr memptr);

/// executer_redir_setter.c
void				set_input_redir(int **pipe_fd, t_command_table **command,
						t_memptr memptr);
void				set_output_redir(int **pipe_fd, t_command_table **command,
						t_memptr memptr);
void				close_redir_pipes(int **pipe_fd, t_command_table **command,
						t_memptr memptr);

/// executer_cmd_checker.c
void				check_builtin(t_command_table *current);
void				check_executables(t_command_table *current,
						char **path_list, t_memptr memptr);
int					check_commands(t_command_table **command_table,
						char **path_list, t_memptr memptr);

/// executer_get_path.c
char				**get_path_list(t_memptr *memptr);
void				fill_in_result_from_path_list(char **path_list,
						char **result, t_memptr memptr);

/// executer.c
int					execute_single_builtin(t_command_table *current,
						char **envp, t_memptr memptr);
int					execute_builtin(t_command_table *current,
						char **envp, t_memptr memptr);
void				process_parent(int process_num, t_memptr *memptr, int pid);
void				process_forks(t_command_table **command_table, char **envp,
						int process_num, t_memptr memptr);
void				close_remaining_pipes(t_command_table *current, int **pipe_fd, 
						t_memptr memptr);

/// signals.c
void				set_signal(void);
void				set_signal_during_processes_child(void);
void				set_signal_during_processes_parent(void);

/// signals_handler.c
void				sigint_handler(int signum);
void				sigint_handler_during_processes_child(int signum);
void				sigint_handler_during_processes_parent(int signum);

//env2.c
int					env(char **argv);

///export.c
int					export(char **argv);
int					ft_export_loop(t_env *envv, t_export *exp, char **argv);
int					ft_export_new(t_env *envv, t_export *exp, char **argv);
int					ft_export_loop2(t_env *envv, t_export *exp, char **argv, char *str);
void				ft_split_var(t_export *exp, char **argv);

///export2.c
int					export_only(t_env *environment);

///export3.c
int					export_special(t_env *envv, t_export *exp);
int					export_wd(t_env *envv, t_export *exp, char **argv);

///export4.c
int					export_input_error(char **argv);
int					check_argv_var(char *argv);
int					export2(char **argv, t_export *exp, t_env *envv);
int					ft_export_found(t_env *envv, t_export *exp, char **argv);

///unset.c
int					unset(char **argv);

///cd.c
void				ft_update_env_var(t_env *envv, char *var, char *value);
int					cd(char **argv);
char				*find_home(t_env *envv);
int					ft_cd_home(t_env *envv);
int					ft_cd2(char **argv, t_env *envv);

///cd2.c
int					ft_check_cd(char *str, t_env *envv);
int					ft_exit_cd(char **cwd, int exit_status);

///pwd.c
int					pwd(void);

///echo.c
int					echo(char **args);
int					check_echo_arg(char *args);
char				*get_echo_var(char *str);
int					contains_str(const char *str1, char *str2);

///echo2.c
int					print_echo(char **args, bool print_newline, int i);
int					check_hifen(char *args, int *n, int i);

///get_set.c
char				*get_env_var_value(t_env *envv, char *var);
void				set_envv(t_env *envv);
t_env				*get_envv(void);

///get_set2.c
t_env				*init_envv(char **envp);
void				free_envv(t_env *envv);
int					reinit_env_var(t_env *envv, char **argv);

///exit.c
int					ft_exit_status(t_command_table *current);
int					exit_status2(t_command_table *current, int count);
int					exit_status3(t_command_table *current);
int					ft_word_count(char **str);
int					check_arg_exit(t_command_table *current);

///exit2.c
void				ft_exit(char *command, char **envp, t_command_table *current);
/* static char			*posnum(char *str, long long n, int len);
static char			*negnum(char *str, long long n, int len);
static int			int_len(long long n); */
char				*ft_ltoa(long long n);

#endif