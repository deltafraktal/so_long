# ══════════════════════════════════════════════════════════════════════════════
#  so_long — Makefile
# ══════════════════════════════════════════════════════════════════════════════

NAME        = so_long
NAME_B        = so_long_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f
SRC_DIR     = src
SRC_B_DIR   = src/bonus
OBJ_DIR     = obj
OBJ_B_DIR     = obj/bonus

# ── Colors ────────────────────────────────────────────────────────────────────
END         := \033[0m
BOLD        := \033[1m
GREEN       := \033[32m
BLUE        := \033[34m
PURPLE      := \033[35m
YELLOW      := \033[33m

# ── OS detection ──────────────────────────────────────────────────────────────
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    $(info 🍎  macOS detected → OpenGL/AppKit)
	MLX_DIR  = minilibx_opengl_20191021-1
	MLX_LIB  = $(MLX_DIR)/libmlx.a
    MLX_FLAG = -Lminilibx_opengl_20191021-1 -lmlx -framework OpenGL -framework AppKit
    INC      = -Imlx -Iinclude
else
    $(info 🐧  Linux detected → X11/Xext)
	MLX_DIR  = minilibx-linux
	MLX_LIB  = $(MLX_DIR)/libmlx.a
    MLX_FLAG = -Lminilibx-linux -lmlx -L/usr/lib/X11 -lXext -lX11
    INC      = -I/usr/include -Imlx -Iinclude
endif

$(info 🔗 MLX_FLAG = $(MLX_FLAG))
# ──────────────────────────────────────────────────────────────────────────────

LIBFT       = libft/libft.a

SRCS        = \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/init_game.c \
	$(SRC_DIR)/mlx-utils.c \
	$(SRC_DIR)/error_and_free.c \
    $(SRC_DIR)/parse_and_set.c \
	$(SRC_DIR)/check_map_and_path.c \
	$(SRC_DIR)/render.c \
    $(SRC_DIR)/utils.c

SRCS_B		= \
	$(SRC_B_DIR)/main.c \
    $(SRC_B_DIR)/init_game.c \
	$(SRC_B_DIR)/handle-keys.c \
	$(SRC_B_DIR)/close-game-window.c \
	$(SRC_B_DIR)/error_and_free.c \
	$(SRC_B_DIR)/free_textures.c \
    $(SRC_B_DIR)/parse_and_set.c \
	$(SRC_B_DIR)/check_map_and_path.c \
	$(SRC_B_DIR)/render.c \
	$(SRC_B_DIR)/animations.c \
	$(SRC_B_DIR)/pop_up.c \
	$(SRC_B_DIR)/enemies.c \
	$(SRC_B_DIR)/camera.c \
    $(SRC_B_DIR)/utils.c

OBJ         = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_B       = $(SRCS_B:$(SRC_B_DIR)/%.c=$(OBJ_B_DIR)/%.o)

TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE = 0

# ── Targets ───────────────────────────────────────────────────────────────────

all: $(NAME) ascii

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	@echo "$(BOLD)$(BLUE)🔗 Linking executable...$(END)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAG) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✔ $(NAME) built successfully$(END)"

# ── Targets bonus ───────────────────────────────────────────────────────────────────
bonus: $(LIBFT) $(MLX_LIB) $(OBJ_B)
	@echo "$(BOLD)$(BLUE)🔗 Linking executable BONUS...$(END)"
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) $(MLX_FLAG) -o $(NAME_B)
	@echo "$(BOLD)$(GREEN)✔ $(NAME_B) built BONUS successfully$(END)"

# ── Libraries ─────────────────────────────────────────────────────────────────

$(LIBFT):
	@echo "$(BOLD)$(YELLOW)→ Building libft...$(END)"
	@$(MAKE) -C libft --silent

# Auto-compile mlx only if libmlx.a doesn't exist yet
$(MLX_LIB):
	@echo "$(BOLD)$(YELLOW)→ Building mlx ($(MLX_DIR))...$(END)"
	@$(MAKE) -C $(MLX_DIR) --silent
	@echo "$(GREEN)✔ mlx compiled$(END)"

# ── Compilation ───────────────────────────────────────────────────────────────

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@printf "$(BOLD)$(PURPLE)⚡ [%2d/%2d] Compiling %-30s$(END)" \
		$(CURRENT_FILE) $(TOTAL_FILES) "$<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo " $(GREEN)✓$(END)"

# ── Clean ─────────────────────────────────────────────────────────────────────

clean:
	@echo "$(BOLD)$(YELLOW)🧹 Cleaning objects...$(END)"
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_B_DIR)
#	@$(MAKE) -C libft clean --silent
#	@$(MAKE) -C $(MLX_DIR) clean --silent

fclean: clean
	@echo "$(BOLD)$(YELLOW)🗑  Removing executable...$(END)"
	@$(RM) $(NAME)
	@$(RM) $(NAME_B)
#	@$(MAKE) -C libft fclean --silent

superclean: fclean
	@echo "$(BOLD)$(YELLOW)BIG CLEANING...$(END)"
	@$(MAKE) -C libft fclean --silent
	@$(MAKE) -C $(MLX_DIR) clean --silent

re: fclean all

mlx: MLX_DIR = mlx
mlx: MLX_LIB = mlx/libmlx.a
mlx: MLX_FLAG = -L mlx -lmlx -framework OpenGL -framework AppKit
mlx: $(NAME)
	@echo "$(GREEN)✔ built with ./mlx$(END)"mlx: MLX_DIR = mlx
mlx: MLX_LIB = mlx/libmlx.a
mlx: MLX_FLAG = -L mlx -lmlx -framework OpenGL -framework AppKit
mlx: $(NAME)
	@echo "$(GREEN)✔ built with ./mlx$(END)"
# ── ASCII art ─────────────────────────────────────────────────────────────────

ascii:
	@echo "$(BOLD)$(PURPLE)"
	@if [ -f ascii_art.txt ]; then cat ascii_art.txt; fi
	@echo "$(END)"
	@echo "$(BOLD)$(GREEN)✨ so_long is ready ✨$(END)"
	@echo "$(YELLOW)➜  use ./$(NAME) <map.ber>$(END)"

.PHONY: all clean fclean re ascii mlx bonus superclean