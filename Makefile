GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

CC = cc
INCLUDE = -I./mandatory/includes 
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

SRC_PATH = ./mandatory/sources
SRC = $(SRC_PATH)/pipex.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = pipex

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
				@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
				@echo "$(GREEN)Compilation of Push Swap project is complete.$(RESET)\n"


$(LIBFT):
			@echo "\n$(CYAN)Compiling$(RESET) $(YELLOW)Libft$(RESET)...\n"
			@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
		@echo "Cleaning $(YELLOW)Push Swap$(RESET) object files..."
		@rm -rf $(OBJ) 
		@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: 
		@echo "\n$(GREEN)Cleaning all...$(RESET)"
		@echo "Cleaning $(YELLOW)Push Swap$(RESET) object files..."
		@rm -rf $(OBJ) 
		@rm -rf $(NAME)
		@echo "Cleaning $(YELLOW)Executable$(RESET) file..."
		@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
		@echo "Cleaning $(YELLOW)Libft.a$(RESET) static library file..."

re: fclean all

%.o: %.c
		@echo "Compiling $<"
		@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re