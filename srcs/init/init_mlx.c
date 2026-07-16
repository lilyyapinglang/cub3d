#include "../../includes/cub3d.h"

void	init_mlx(t_game *game)
{
	int	width_pixel;
	int	height_pixel;
	int	screen_width;
	int	screen_height;

	width_pixel = WIN_W;
	height_pixel = WIN_H;
	game->mlx = mlx_init();
	if (!game->mlx)
		graceful_exit(game, err_msg("mlx", ERR_MLX_INIT, 1));
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (width_pixel <= 0 || height_pixel <= 0 || width_pixel > screen_width
		|| height_pixel > screen_height)
		graceful_exit(game, err_msg("mlx", ERR_MLX_OUT_SCREEN, 1));
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H,
			"Welcome to Magic Game!");
	if (!game->win)
		graceful_exit(game, err_msg("mlx", ERR_MLX_WIN, 1));
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
}
