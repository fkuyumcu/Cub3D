NAME = cub3D

CC = cc
CFLAGS = -fPIE -g  -Wall -Wextra -Werror
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
	  ./exec/ray_cast.c \
	  ./gnl/get_next_line.c \
	  ./gnl/get_next_line_utils.c \
	  ./parser/parser.c \
	  ./parser/end.c \
	  ./parser/file.c \
	  ./parser/map.c \
	  ./parser/parser_utils.c \

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