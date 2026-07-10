#include "../../includes/cub3d.h"

// hit the wall -> stop  , not conituning
// if not hit the all, update positions.

int	check_hit_wall(t_game *game)
{
	//
	if (game->map.grid[(int)game->player.pos_x][(int)game->player.pos_y] == 1)
		return (1);
	return (0);
}