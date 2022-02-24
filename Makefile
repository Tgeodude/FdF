FRAMEWORKS=-framework OpenGL -framework AppKit -L/usr/lib -lmlx
FLAGS=-Werror -Wextra -Wall
NAME=fdf
SRCS=*.c
INCLUDES=libft/libft.a
HEADER=fdf.h

all: $(NAME)

$(NAME): $(HEADER)
	make -C libft/
	cc $(SRCS) -o $(NAME) $(FLAGS) -Imlx $(INCLUDES) $(FRAMEWORKS)

clean:
	@make -C libft/ clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re bonus
