CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g

NAME		= fractol

LIB_DIR		= ./lib

LIB			= $(LIB_DIR)/libftplus.a

MLX_DIR		= ./minilibx-linux

MLX_LIB		= $(MLX_DIR)/libmlx.a

MLX_URL		= https://github.com/42Paris/minilibx-linux

MLXFLAGS  	= -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

INCLUDES	= -I$(LIB_DIR)/incs -I$(INCS_DIR) -I$(MLX_DIR)

INCS_DIR	= ./incs

INCS 		= $(INCS_DIR)/fractol.h

OBJS_DIR	= ./objs

OBJS		= $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

SRCS_DIR	= ./srcs

SRCS		= main.c manage_program.c manage_graphic.c image.c mandelbrot.c julia.c bonus.c

SEP			= "\n------------------------------------------------------------\n"

all: $(NAME)

$(NAME): $(LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX_LIB) $(MLXFLAGS) -o $(NAME)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(MLX_LIB): | $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(MLX_DIR):
	@echo $(SEP)
	@echo "Missing library minilibx.\nDownloading from $(MLX_URL)"
	@echo $(SEP)
	@mkdir -p $(MLX_DIR)
	@git clone $(MLX_URL) $(MLX_DIR)
	@chmod +x $(MLX_DIR)/configure

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_DIR)/$(MLX_LIB)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

del_lib:
	@echo $(SEP)
	@echo "Deleting library libftplus..."
	@echo $(SEP)
	$(MAKE) -C $(LIB_DIR) del_lib
	@echo $(SEP)
	@echo "Deleting library minilibx..."
	@echo $(SEP)
	@rm -rf $(MLX_DIR)

.PHONY: all clean fclean re del_lib
