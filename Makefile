# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/01/22 12:59:57 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ls

SRC=srcs/check.c\
	srcs/reading.c\
	srcs/output.c\
	srcs/calc.c
	
INCLUDES=includes

LIB=libft

all: $(NAME)

$(NAME):
			@make re -C $(LIB)
			@gcc -o $(NAME) main.c $(SRC) -I libft/includes -I $(INCLUDES) -L $(LIB) -lft

clean:
			@make clean -C $(LIB)

fclean: clean
			@make fclean -C $(LIB)
			@rm -f $(NAME)

re: fclean all