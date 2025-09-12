# Compiler
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -I include -I libft/include

# Directories
OBJDIR	:= objs
LIBDIR	:= libft/lib

# Executable
NAME	:= minishell

# Source files
SRC		:= $(shell find srcs -name "*.c")

# Object files
OBJ		:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Libft
LIBFT	:= $(LIBDIR)/libft.a

# Colors
GREEN	:= \033[0;32m
CYAN	:= \033[0;36m
YELLOW	:= \033[1;33m
RESET	:= \033[0m

# Default rule
.DEFAULT_GOAL := all

# Build rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(CYAN)🚀 Built: $@$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)🛠️  Compiled:$(RESET) $<"

$(LIBFT):
	@make -C libft

clean:
	@rm -rf $(OBJDIR)
	@make -C libft clean
	@echo "$(YELLOW)🧹 Cleaned object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "$(YELLOW)🗑️  Removed binary.$(RESET)"

re: fclean all

.PHONY: all clean fclean re