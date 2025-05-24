NAME = cub3D

CC = cc
CFLAGS = # -Wall -Wextra -Werror
LIBRARY = -Lminilibx-linux -lmlx -lX11 -lXext -lm -g
MINILIBX = minilibx-linux/
SRC = main.c \
      cube_utils.c \
      player.c\

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(MINILIBX)
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