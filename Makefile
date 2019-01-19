NAME=ls

SRC=srcs/check.c

INCLUDES=includes

LIB=libft

all: $(NAME)

$(NAME):
			make re -C $(LIB)
			gcc -o $(NAME) main.c $(SRC) -I libft/includes -I $(INCLUDES) -L $(LIB) -lft

clean:
			make clean -C $(LIB)

fclean: clean
			make fclean -C $(LIB)
			rm -f $(NAME)

re: fclean all