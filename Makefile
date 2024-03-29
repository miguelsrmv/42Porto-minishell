# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2024/03/29 16:04:09 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   minishell

CC      = 	cc

CFLAGS   =  -Wall -Wextra -Werror -g

SRCDIR	=	src

INCDIR	=   includes

LIBFTDIR =  src/libft

LIBS	=   -L$(LIBFTDIR) -lft -lreadline

INCFLAGS =  -I $(INCDIR) -I $(LIBFTDIR)

SRC		=	main.c bash_main.c \
			clean/exit_error.c clean/clean_memory.c clean/clean_memory_heredoc.c \
			clean/clean_memory_pipes.c \
			prepare_shell/path_update.c prepare_shell/shell_update.c \
			lexer/get_input.c lexer/input_checker.c lexer/lexer.c \
			lexer/lexer_linked_list.c lexer/lexer_get_tokens.c lexer/fork_input.c \
			parser/parser.c parser/parser_set_redirs.c parser/parser_heredoc.c \
			parser/clean_heredocs.c parser/parser_heredoc_parent.c \
			parser/parser_heredoc_child.c \
			expander/expander.c expander/expander_noquotes.c expander/expander_squote.c \
			expander/expander_dquote.c expander/expander_concatenate.c \
			executer/executer_prepare_processes.c executer/executer_redir_checker.c \
			executer/executer_redir_setter.c executer/executer_executable_checker.c \
			executer/executer_dir_checker.c executer/executer_get_path.c \
			executer/executer_childparent_processes.c executer/executer_single_builtin.c \
			executer/executer_input_check.c executer/executer_process_check.c \
			executer/executer_output_check.c executer/executer_command_check.c \
			executer/final_nullstrings.c \
			signals/signals.c signals/signals_handler.c signals/signals_handler_input.c \
			builtins/builtin_cd.c builtins/builtin_cd2.c builtins/builtin_echo.c \
			builtins/builtin_echo2.c  builtins/builtin_env.c \
			builtins/builtin_export.c builtins/builtin_export2.c \
			builtins/builtin_export3.c builtins/builtin_export4.c builtins/builtin_pwd.c \
			builtins/builtin_unset.c builtins/get_set.c builtins/get_set2.c \
			builtins/builtin_exit.c builtins/builtin_exit2.c builtins/builtin_checker.c

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

libft:
	@ cd $(LIBFTDIR) && make

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re: fclean all


# Estes aqui servem para avaliar leaks ignorando os leaks do readline!

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

readline.supp:
	@ echo "{" > readline.supp
	@ echo "    leak readline" >> readline.supp
	@ echo "    Memcheck:Leak" >> readline.supp
	@ echo "    ..." >> readline.supp
	@ echo "    fun:readline" >> readline.supp
	@ echo "}" >> readline.supp
	@ echo "{" >> readline.supp
	@ echo "    leak add_history" >> readline.supp
	@ echo "    Memcheck:Leak" >> readline.supp
	@ echo "    ..." >> readline.supp
	@ echo "    fun:add_history" >> readline.supp
	@ echo "}" >> readline.supp
		
test:
	valgrind -q --leak-check=full --trace-children=yes --track-fds=yes ./minishell

.PHONY: all clean fclean re libft
