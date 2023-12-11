/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/11 22:57:20 by mde-sa--         ###   ########.fr       */
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
# define EOF_ERROR "exit\n"

// Usage errors
# define USAGE_ERROR "Usage error: \'./minishell\'.\n"
# define QUOTE_ERROR "Input error: unclosed quote.\n"
# define SYNTAX_ERROR "Syntax error near unexpected token.\n"
# define COMMAND_ERROR "command not found.\n"
# define OPEN_ERROR "No such file or directory.\n"
# define DIRECTORY_ERROR "Is a directory\n"

enum e_SignalType {
	NO_SIGNAL,
	SIGINT_SIGNAL,
	EOF_SIGNAL
};

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
						t_command_table **command_table, char **envp);

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
void				expand_to_number(char **string, int *start, t_memptr memptr,
						enum e_ExpandType expand_number);
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
void				expand_to_number_quotes(char **string, int *start, int*end,
						t_memptr memptr);

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
void				check_redirections(int **pipe_fd, t_command_table **command,
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
int					execute_builtin(t_command_table *current,
						char **envp, t_memptr memptr);
void				process_parent(int process_num,
						t_memptr *memptr);
void				process_forks(t_command_table **command_table, char **envp,
						int process_num, t_memptr memptr);

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
//static int		ft_export_new(t_env *envv, t_export *exp, char **argv);
//static int		ft_export_found(t_env *envv, t_export *exp, char **argv);
//static void		ft_split_var(t_export *exp, char **argv);
//static int		ft_export_loop(t_env *envv, t_export *exp, char **argv);
int					export(char **argv);

///export2.c
//static int		ft_print_with_value(char **env_var_cpy, int i);
//static int		ft_export_exit(char ***array, bool exit_status);
//static int		ft_sort_loop(char **env_var_cpy, int i, int j);
int					export_only(t_env *environment);

///export3.c
int					export_special(t_env *envv, t_export *exp);
int					export_wd(t_env *envv, t_export *exp, char **argv);

///export4.c
//static int	export_error_loop(char **var, char **argv);
int					export_input_error(char **argv);

///unset.c
//static char		*ft_get_var(t_env *envv, int i);
//static void		ft_del_var(t_env *envv, int i);
//static int		ft_inner_loop(char **argv, t_env *envv, int i, int k);
int					unset(char **argv);

///cd.c
//static char	*find_home(t_env *envv);
//static void	ft_update_env_var(t_env *envv, char *var, char *value);
//static int	ft_exit_cd(char **cwd, int exit_status);
//static int	ft_cd_home(t_env *envv);
int					cd(char **argv);

///pwd.c
int					pwd(void);

///echo.c
int					echo(char **args);
char   				*ft_strchr2(const char *s, int c);
char    			*get_echo_var(char *str);
int					containsStr(const char *str1, char *str2);

///exit.c
//static bool		is_valid_exit_arg(char **args);
int					exit_inbuilt(char **args);

///get_set.c
//static void		get_env_var_value_utils(t_env *envv, char *var,
//						char **value, int i);
char				*get_env_var_value(t_env *envv, char *var);
t_env				*init_envv(char **envp);
void				free_envv(t_env *envv);
//static char		**_get_envp(char **envp, bool reset);
void				set_envp(char **envp);
//static t_env	*_get_envv(t_env *envv);
void				set_envv(t_env *envv);
t_env				*get_envv(void);
int					reinit_env_var(t_env *envv, char **argv);

#endif