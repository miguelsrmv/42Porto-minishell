# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2024/02/03 08:51:41 by mde-sa--         ###   ########.fr        #
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

SRC		=	main.c bash_main.c exit_error.c clean_memory.c \
			lexer/get_input.c lexer/input_checker.c \
			lexer/lexer.c lexer/lexer_linked_list.c lexer/lexer_get_tokens.c \
			parser/parser.c parser/parser_set_redirs.c parser/parser_heredoc.c \
			expander/expander.c expander/expander_noquotes.c expander/expander_squote.c \
			expander/expander_dquote.c expander/expander_concatenate.c \
			executer/executer_prepare_processes.c executer/executer_redir_checker.c \
			executer/executer_redir_checker2.c executer/executer_redir_setter.c \
			executer/executer_cmd_checker.c executer/executer_executable_checker.c \
			executer/executer_get_path.c executer/executer_childparent_processes.c \
			executer/executer.c \
			signals/signals.c signals/signals_handler.c \
			builtins/builtin_cd.c builtins/builtin_cd2.c builtins/builtin_echo.c \
			builtins/builtin_echo2.c  builtins/builtin_env2.c \
			builtins/builtin_export.c builtins/builtin_export2.c \
			builtins/builtin_export3.c builtins/builtin_export4.c builtins/builtin_pwd.c \
			builtins/builtin_unset.c builtins/get_set.c builtins/get_set2.c \
			builtins/builtin_exit.c builtins/builtin_exit2.c

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft $(NAME)

$(NAME): $(OBJS) 
	@ $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	@ $(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

libft:
	@ cd $(LIBFTDIR) && make -s

clean:
	@ $(MAKE) -sC $(LIBFTDIR) clean
	@ $(RM) $(OBJS)

fclean: clean
	@ $(MAKE) -sC $(LIBFTDIR) fclean
	@ $(RM) $(NAME)

re: fclean all


# Estes aqui servem para avaliar leaks ignorando os leaks do readline!

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-file=output.log ./minishell

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

.PHONY: all clean fclean re libft
