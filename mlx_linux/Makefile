FLAGS=-Werror -Wextra -Wall
NAME=fdf
SRC= main.c \
     get_next_line.c \
     get_next_line_utils.c \
     map_creator.c \

INCLUDES=libft/libft.a

all:	$(OBJ) fdf.h
	@make -C libft/ all
	gcc $(SRC) -o $(NAME) $(FLAGS) $(INCLUDES)

clean:
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
