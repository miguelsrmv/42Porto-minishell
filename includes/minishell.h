/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/11 16:21:32 by mde-sa--         ###   ########.fr       */
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

# define NOT_IN_QUOTE 0
# define QUOTE_START 1
# define QUOTE_END 2

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



// Function definitions
void exit_error(char *error_message);

/// lexer.c
char	**readline_split(const char *s);

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

#endif