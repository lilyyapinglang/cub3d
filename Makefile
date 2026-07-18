NAME        = cub3d

CC          = cc
CFLAGS = -Wall -Wextra -Werror -g3 -std=gnu17 -Iincludes -Ilibft -Iminilibx-linux
LDFLAGS     = -lXext -lX11 -lm

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX         = $(MLX_DIR)/libmlx.a

SRCS_DIR    = srcs
OBJS_DIR    = objs
INIT_DIR    = $(SRCS_DIR)/init
PARSE_DIR   = $(SRCS_DIR)/parsing
EXIT_DIR    = $(SRCS_DIR)/exit
RENDER_DIR  = $(SRCS_DIR)/render

SRCS        = $(SRCS_DIR)/main.c \
              $(INIT_DIR)/init_main.c \
              $(INIT_DIR)/init_mlx.c \
              $(INIT_DIR)/init_player.c \
              $(PARSE_DIR)/parse_input.c \
              $(PARSE_DIR)/check_input.c \
              $(PARSE_DIR)/check_map_texture.c \
              $(PARSE_DIR)/process_cub_file.c \
              $(PARSE_DIR)/generate_map.c \
              $(PARSE_DIR)/check_map_borders.c \
              $(PARSE_DIR)/check_map_contents.c \
              $(PARSE_DIR)/utils.c \
              $(EXIT_DIR)/error.c \
              $(EXIT_DIR)/exit.c \
              $(EXIT_DIR)/free.c \
			  $(RENDER_DIR)/movement.c \
			  $(RENDER_DIR)/rotate.c\
			  $(RENDER_DIR)/draw.c \
			  $(RENDER_DIR)/event.c \
			  $(RENDER_DIR)/render.c \
			  $(RENDER_DIR)/minimap.c \
			  $(RENDER_DIR)/collision.c\
			  $(RENDER_DIR)/raycasting_1.c \
			  $(RENDER_DIR)/raycasting_2.c \
			  $(RENDER_DIR)/texture.c 

OBJS        = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
