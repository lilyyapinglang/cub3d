NAME        = cub3d

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -Ilibft -Iminilibx-linux
LDFLAGS     = -lXext -lX11 -lm

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX         = $(MLX_DIR)/libmlx.a

SRCS_DIR    = srcs
INIT_DIR    = $(SRCS_DIR)/init
EXIT_DIR    = $(SRCS_DIR)/exit

SRCS        = $(SRCS_DIR)/main.c \
              $(INIT_DIR)/init_main.c \
              $(INIT_DIR)/init_mlx.c \
              $(EXIT_DIR)/error.c \
              $(EXIT_DIR)/exit.c \
              $(EXIT_DIR)/free.c

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
