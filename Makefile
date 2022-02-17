FLAGS=-Werror -Wextra -Wall -g
NAME=fdf
SRC=*.c
INCLUDES=libft/libft.a

all:
	@make -C libft/ all
	gcc $(SRC) -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(FLAGS) $(INCLUDES) 

clean:
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all
