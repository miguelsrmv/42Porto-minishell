/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/31 16:12:54 by bmota-si         ###   ########.fr       */
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
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <fcntl.h>


// Structs
typedef struct s_minishell {
	char *init_str;
	char *expanded_str;
	char *command;
	char **args;
	char *joined_path;
	int fd_input;
	int fd_output;
	char *pwd;
	char **env;
	char **new_env;
}	t_minishell;

typedef struct s_split_numbers {
	int		word_count;
	int		in_word;
	int		in_quote;
	char	quote_char;
	size_t	i;
}	t_split_numbers;

// Function definitions
/// ft_command_split.c
char	**ft_command_split(const char *s);
void	ft_init_struct(t_minishell *shell);
char    *ft_strtok(char *str, char *a);
int 	minishell_pwd(char **args);
int 	minishell_exit(char **args); 
int 	minishell_env(char **env);


/*Builtins*/
int     ft_builtins(t_minishell *shell);
int     minishell_export(t_minishell *shell);
char    *env_to_str(char **new_env);
int     str_env_len(char **env);
void    sort_env(char **tab, int env_len);
void    print_sorted_env(char **new_env);

//void    execute_pwd(char *str);


#endif