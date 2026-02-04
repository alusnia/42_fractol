# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Executable Name
NAME = fractol

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

# MiniLibX Library
MLX_DIR   = ./minilibx-linux
MLX_LIB   = $(MLX_DIR)/libmlx.a

FILES = main.c manage_program.c manage_graphic.c image.c mandelbrot.c julia.c bonus.c

# Object Files
OBJS = $(FILES:.c=.o)

# Headers
HEADERS = fractol.h $(LIBFT_DIR)/libft.h


INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)


LFLAGS  = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lX11 -lXext -lm

# Default target
all: $(NAME)

# Build executable
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

# Compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build MiniLibX
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

# Remove executables and object files
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
