#NAMES
NAME		= fdf
MAKE		= make

#COMP USE CC INSTEAD?!?!??!
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

#LIBFT
LIBFT_DIR	= libft
LIBFT		= libft.a
LIBFT_MAKE	= cd $(LIBFT_DIR) && $(MAKE)
LIBFT_INC	= -L libft -lft

#MINILIBX STATIC
MLXDIR		= MLX
MLXMAKE		= cd $(MLXDIR) && $(MAKE)
MLX_INC		= -Lmlx -lmlx -framework OpenGL -framework AppKit

#SRC
SRC_DIR		= src
SRC			= $(SRC_DIR)/fdf.c \
			$(SRC_DIR)/drawMap.c \
			$(SRC_DIR)/exit.c  \
			$(SRC_DIR)/get_next_line.c\
			$(SRC_DIR)/get_next_line_utils.c \
			$(SRC_DIR)/map_creator.c \
			$(SRC_DIR)/map_hex.c \
			$(SRC_DIR)/validation.c \

SRC_BON_DIR	= src_bonus
SRC_BON		= $(SRC_BON_DIR)/fdf_bonus.c  \
			$(SRC_BON_DIR)/drawMap_bonus.c  \
			$(SRC_BON_DIR)/get_next_line.c \
			$(SRC_BON_DIR)/get_next_line_utils.c \
			$(SRC_BON_DIR)/hooks_bonus.c \
			$(SRC_BON_DIR)/map_creator_bonus.c \
			$(SRC_BON_DIR)/map_hex_bonus.c \
			$(SRC_BON_DIR)/validation_bonus.c \
			$(SRC_BON_DIR)/drawRotation_bonus.c \


#INC
INC_DIR		= inc
INC			= $(INC_DIR) fdf.h
INC_BON_DIR		= inc_bonus
INC_BON		= $(INC_BON_DIR) fdf_bonus.h

#OBJ
OBJ_DIR		= obj
OBJ			= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))
OBJ_BON_DIR		= obj_bonus
OBJ_BON		= $(patsubst $(SRC_BON_DIR)%, $(OBJ_BON_DIR)%, $(SRC_BON:.c=.o))

#OBJ_INC
OBJ_INC		= -I mlx -I $(INC_DIR) -I libft
OBJ_BON_INC	= -I mlx -I $(INC_BON_DIR) -I libft

#RMS
RM_DIR		= rm -rf
RM_FILE		= rm -f

#DEPS
$(NAME): $(OBJ)
	$(MLXMAKE)
	$(LIBFT_MAKE)
	$(CC) $(OBJ) $(LIBFT_INC) $(MLX_INC) -o $(NAME)

#OBJ DEPS
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(OBJ_INC) -c $< -o $@

$(OBJ_BON_DIR)/%.o: $(SRC_BON_DIR)/%.c
	$(CC) $(CFLAGS) $(OBJ_BON_INC) -c $< -o $@

$(OBJ)		:	| $(OBJ_DIR)
$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_BON)		:	| $(OBJ_BON_DIR)
$(OBJ_BON_DIR):
			mkdir -p $(OBJ_BON_DIR)


#RULES
all:	$(NAME)

bonus:	fclean $(NAME) $(OBJ_BON)
		$(MLXMAKE)
		$(LIBFT_MAKE)
		$(CC) $(OBJ_BON) $(LIBFT_INC) $(MLX_INC) -o $(NAME)

clean:
		${RM_DIR} ${OBJ_DIR}
		${RM_DIR} ${OBJ_BON_DIR}


fclean:	clean
		${RM_FILE} $(NAME)
		cd $(LIBFT_DIR) && $(MAKE) fclean
		cd $(MLXDIR) && $(MAKE) clean

re:		fclean all

#OTHER
.PHONY: all clean fclean re
