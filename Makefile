NAME        = cub3D 
BONUS_NAME	= cub3D_bonus

CC          = cc
CFLAGS = -Wall -Wextra -Werror  -Iincludes -Ilibft -Iminilibx-linux -g3 -std=gnu17
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
BONUS_DIR 	= srcs_bonus

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
			  $(RENDER_DIR)/event.c \
			  $(RENDER_DIR)/render.c \
			  $(RENDER_DIR)/collision.c\
			  $(RENDER_DIR)/raycasting_1.c \
			  $(RENDER_DIR)/raycasting_2.c \
			  $(RENDER_DIR)/texture.c \
			  $(RENDER_DIR)/floor_n_ceiling.c

BONUS_SRCS 	= $(SRCS_DIR)/main.c \
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
			  $(RENDER_DIR)/event.c \
			  $(RENDER_DIR)/collision.c\
			  $(RENDER_DIR)/raycasting_1.c \
			  $(RENDER_DIR)/raycasting_2.c \
			  $(RENDER_DIR)/texture.c \
			  $(RENDER_DIR)/floor_n_ceiling.c\
			  $(BONUS_DIR)/draw_bonus.c\
			  $(BONUS_DIR)/minimap_bonus.c\
			  $(BONUS_DIR)/render_bonus.c


OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))
BONUS_OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(BONUS_SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(MLX) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(BONUS_NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all bonus

.PHONY: all clean fclean re
