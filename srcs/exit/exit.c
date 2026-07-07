#include "../../includes/cub3d.h"

void	graceful_exit(t_game *game, int code)
{
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_all(game);
	exit(code);
}

int	handle_exit(t_game *game)
{
	graceful_exit(game, 0);
	return (0);
}
