GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

CC = cc
INCLUDE = -I./mandatory/includes
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

SRC_PATH = ./mandatory/sources
SRC = $(SRC_PATH)/pipex.c $(SRC_PATH)/build_command.c $(SRC_PATH)/utils.c $(SRC_PATH)/execute_commands.c

OBJ_DIR = tmp
OBJ = $(OBJ_DIR)/pipex.o $(OBJ_DIR)/build_command.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/execute_commands.o

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = pipex

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)Compilation of Pipex project is complete.$(RESET)\n"

$(LIBFT):
		@echo "\n$(CYAN)Compiling$(RESET) $(YELLOW)Libft$(RESET)...\n"
		@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
		@echo "Cleaning $(YELLOW)Pipex$(RESET) object files..."
		@rm -rf $(OBJ_DIR)
		@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: 
		@echo "\n$(GREEN)Cleaning all...$(RESET)"
		@echo "Cleaning $(YELLOW)Pipex$(RESET) object files..."
		@rm -rf $(OBJ_DIR)
		@rm -rf $(NAME)
		@echo "Cleaning $(YELLOW)Executable$(RESET) BONUS file..."
		@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
		@echo "Cleaning $(YELLOW)Libft.a$(RESET) static library file..."

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
		@mkdir -p $(OBJ_DIR)
		@echo "Compiling $<"
		@$(CC) $(CFLAGS) -c $< -o $@


.PHONY: all clean fclean re bonus
