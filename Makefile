NAME = cub3D

CC = cc
CFLAGS =   -Wall -Wextra -Werror
LIBRARY = -Lminilibx-linux -lmlx -lX11 -lXext -lm
MINILIBX = minilibx-linux/
SRC = main.c \
      ./exec/player.c\
	  ./exec/inits.c \
	  ./exec/paint_it_black.c \
	  ./exec/key_actions.c \
	  ./exec/collision.c \
	  ./exec/move.c \
	  ./exec/texture_mapping.c \
	  ./exec/texture_utils.c \
	  ./exec/ray_cast.c \
	  ./gnl/get_next_line.c \
	  ./gnl/get_next_line_utils.c \
	  ./parser/parser.c \
	  ./parser/end.c \
	  ./parser/file.c \
	  ./parser/map.c \
	  ./parser/parser_utils.c \
	  ./parser/utils.c \
	  ./parser/file_desc.c \
	  ./parser/map_check.c \
	  ./parser/parser_checks.c \
	  ./parser/filling.c \
	  ./parser/player.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(MINILIBX)
	@$(CC) $(OBJ) $(CFLAGS) $(LIBRARY) -o $(NAME)

all: $(NAME)

clean:
	make clean -C $(MINILIBX)
	rm -f $(OBJ)

fclean: clean
	make clean -C $(MINILIBX)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re