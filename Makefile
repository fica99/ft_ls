# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/02/27 20:57:18 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

SRC=srcs/check.c\
	srcs/check2.c\
	srcs/reading.c\
	srcs/sort_list.c\
	srcs/flags.c\
	srcs/flags2.c\
	srcs/sort_list2.c\
	srcs/output.c\
	srcs/print_one_level.c\
	srcs/print_rows.c\

INCLUDES=includes

LIB=libft

all: $(NAME)

$(NAME):
			@make re -C $(LIB)
			@gcc -g -o $(NAME) main.c $(SRC) -I libft/includes -I $(INCLUDES) -L $(LIB) -lft

clean:
			@make clean -C $(LIB)

fclean: clean
			@make fclean -C $(LIB)
			@rm -f $(NAME)

re: fclean all