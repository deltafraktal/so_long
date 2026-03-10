NAME	= so_long

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

MLX_DIR	= ../mlx
MLX		= $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC		= main.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	$(CC) $(CFLAGS) $(OBJ)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re