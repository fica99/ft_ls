# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/02/19 22:43:12 by ggrimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

SRC=srcs/check.c\
	srcs/reading.c\
	srcs/sort_list.c\
	srcs/flags.c\
	srcs/flags2.c\
	srcs/sort_list2.c\
	srcs/output.c\
	srcs/print_one_level.c\
	srcs/print_rows.c\
	srcs/flags_binary.c\

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