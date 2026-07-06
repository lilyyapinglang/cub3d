#include "../../includes/cub3d.h"

void	init_mlx(t_game *game)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		graceful_exit(cub, err_msg("mlx", ERR_MLX_INIT, 1));
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	if (!cub->win)
		graceful_exit(cub, err_msg("mlx", ERR_MLX_WIN, 1));
}
