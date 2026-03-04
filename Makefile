NAME = so_long
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_DIR = src
OBJ_DIR = obj

SRCS = \
	$(SRC_DIR)/main.c \
	
OBJ = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Colors
END		:= \033[0m
BOLD	:= \033[1m
GREEN	:= \033[32m
BLUE	:= \033[34m
PURPLE	:= \033[35m
YELLOW	:= \033[33m

TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE = 0

all: $(NAME) ascii

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BOLD)$(BLUE)🔗 Linking executable...$(END)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@printf "$(BOLD)$(PURPLE)⚡ [%2d/%2d] Compiling %-30s$(END)" \
	$(CURRENT_FILE) $(TOTAL_FILES) "$<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo " $(GREEN)✓$(END)"

clean:
	@echo "$(BOLD)$(YELLOW)🧹 Cleaning objects...$(END)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(BOLD)$(YELLOW)🗑 Removing executable...$(END)"
	@$(RM) $(NAME)

re: fclean all

ascii:
	@echo "$(BOLD)$(PURPLE)"
	@if [ -f ascii_art.txt ]; then \
		cat ascii_art.txt; \
	fi
	@echo "$(END)"
	@echo "$(BOLD)$(GREEN)✨ so_long is ready ✨$(END)"
	@echo "$(YELLOW)➜  use ./$(NAME) + the_map_you_want.ber to start the game$(END)"

.PHONY: all clean fclean re ascii