GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

CC = cc
INCLUDE = -I./mandatory/includes
INCLUDE_BONUS = -I./bonus/includes
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)
CFLAGS_BONUS = -Wall -Wextra -Werror -g $(INCLUDE_BONUS)

SRC_PATH = ./mandatory/sources
SRC = $(SRC_PATH)/pipex.c $(SRC_PATH)/build_command.c $(SRC_PATH)/utils.c $(SRC_PATH)/execute_commands.c
SRC_BONUS = ./bonus/sources/pipex_bonus.c ./bonus/sources/build_command_bonus.c ./bonus/sources/utils_bonus.c ./bonus/sources/execute_commands_bonus.c 

OBJ_DIR = tmp
OBJ = $(OBJ_DIR)/pipex.o $(OBJ_DIR)/build_command.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/execute_commands.o
OBJ_BONUS = ./bonus/sources/pipex_bonus.o ./bonus/sources/build_command_bonus.o ./bonus/sources/utils_bonus.o ./bonus/sources/execute_commands_bonus.o

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = pipex
NAME_BONUS = pipex_bonus

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)Compilation of Pipex project is complete.$(RESET)\n"

$(LIBFT):
		@echo "\n$(CYAN)Compiling$(RESET) $(YELLOW)Libft$(RESET)...\n"
		@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT)
		@$(CC) $(CFLAGS_BONUS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)
		@echo "$(GREEN)Compilation of Pipex BONUS is complete.$(RESET)\n"

clean:
		@echo "Cleaning $(YELLOW)Pipex$(RESET) object files..."
		@rm -rf $(OBJ_DIR)
		@rm -rf ./bonus/sources/*.o
		@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: 
		@echo "\n$(GREEN)Cleaning all...$(RESET)"
		@echo "Cleaning $(YELLOW)Pipex$(RESET) object files..."
		@rm -rf $(OBJ_DIR)
		@rm -rf $(NAME)
		@rm -rf $(NAME_BONUS)
		@rm -rf ./bonus/sources/*.o
		@echo "Cleaning $(YELLOW)Executable$(RESET) ./pipex file..."
		@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
		@echo "Cleaning $(YELLOW)Libft.a$(RESET) static library file..."

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
		@mkdir -p $(OBJ_DIR)
		@echo "Compiling $<"
		@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus
