# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/10/22 14:01:39 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   minishell

CC      = 	cc

CFLAGS   =  -g #-Wall -Wextra -Werror

SRCDIR	=	src

INCDIR	=   includes

LIBFTDIR =  src/libft

LIBS	=   -L$(LIBFTDIR) -lft -lreadline

INCFLAGS =  -I $(INCDIR) -I $(LIBFTDIR)

SRC		=	main.c get_input.c lexer.c lexer_linked_list.c lexer_get_tokens.c \
			parser.c parser_redirs.c helper_functions.c

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft $(NAME)

$(NAME): $(OBJS) 
	@ $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	@ $(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

libft:
	@ cd $(LIBFTDIR) && make -s && make -s clean

clean:
	@ $(MAKE) -sC $(LIBFTDIR) clean
	@ $(RM) $(OBJS)

fclean: clean
	@ $(MAKE) -sC $(LIBFTDIR) fclean
	@ $(RM) $(NAME)

re: fclean all


# Estes aqui servem para avaliar leaks ignorando os leaks do readline!

leaks: readline.supp
	@ valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=output.log ./minishell

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

.PHONY: all clean fclean re libft leaks readline.supp
