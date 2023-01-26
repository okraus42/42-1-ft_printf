# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okraus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/14 13:43:18 by okraus            #+#    #+#              #
#    Updated: 2023/01/26 10:31:15 by okraus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_printf.c \
ft_string_pointer.c \
ft_printf_utils.c
OBJ = $(SRC:.c=.o)
INCS = libft.h
LIBC = ar rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(INCS)
	@$(cc) $(CFLAGS) -c $(SRC)

$(NAME): $(OBJ)
	$(LIBC) $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
