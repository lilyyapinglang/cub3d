#include "../../includes/cub3d.h"

void	graceful_exit(t_game *game, int code)
{
	if (cub->win && cub->mlx)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	free_all(cub);
	exit(code);
}

int	handle_exit(t_game *game)
{
	graceful_exit(cub, 0);
	return (0);
}
