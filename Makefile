# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmota-si <bmota-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/10/11 12:52:19 by bmota-si         ###   ########.fr        #
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

SRC		=	main2.c ft_command_split.c ft_init_struct.c builtins.c

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -r


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

.PHONY: all clean fclean re libft
