# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 19:59:42 by mde-sa--          #+#    #+#              #
#    Updated: 2023/12/20 08:49:42 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
			ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
			ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isspace.c \
			ft_isquote.c ft_issquote.c ft_isdquote.c ft_isdigit.c ft_isalnum.c \
			ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
			ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
			ft_itoa.c ft_striteri.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c ft_lstmap.c ft_printf.c ft_printf_string_fd.c ft_printf_base_fd.c \
			ft_printf_char_fd.c ft_printf_int_fd.c ft_printf_ptr_fd.c \
			ft_printf_uns_fd.c ft_fprintf.c get_next_line.c get_next_line_utils.c \
			ft_strcmp.c ft_strcmp_input.c ft_free_tabs.c ft_atoi_base.c ft_swap.c \
			ft_abs.c ft_str_tolower.c ft_str_toupper.c ft_checkextension.c ft_strndup.c \
			ft_str_arr_dup.c ft_str_arr_len.c ft_realloc_str_arr.c ft_free_str_array.c \
			ft_free_str.c ft_strstrjoin.c ft_append.c ft_free.c ft_atol.c ft_issign.c \
			ft_tabdup.c ft_getpid.c ft_getppid.c ft_strchr2.c

OBJ		=	$(SRC:.c=.o)

RM		=	rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@ ar -rcs $(NAME) $(OBJ)

.c.o:
	@ $(CC) $(CFLAGS) -c $< -I . -o $@

clean:
	@ rm -rf $(OBJ)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all
