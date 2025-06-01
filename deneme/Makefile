NAME = cub3D

CC = cc
CFLAGS = -fPIE # -Wall -Wextra -Werror
LIBRARY = #-Lminilibx-linux -lmlx -lX11 -lXext -lm -g
MINILIBX = minilibx-linux/
SRC = main.c \
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
	@$(CC) $(OBJ) $(CFLAGS)  -o $(NAME)

all: $(NAME)

clean:
	make clean -C $(MINILIBX)
	rm -f $(OBJ)

fclean: clean
	make clean -C $(MINILIBX)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re