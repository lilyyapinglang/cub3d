#include "../../includes/cub3d.h"

void	init_all(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.map_width = WIN_W;
	game->map.map_width = WIN_H;
	game->map.grid = NULL;
}
