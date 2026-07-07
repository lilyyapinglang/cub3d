#include "../../includes/cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		graceful_exit(game, err_msg("mlx", ERR_MLX_INIT, 1));
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		graceful_exit(game, err_msg("mlx", ERR_MLX_WIN, 1));
}
