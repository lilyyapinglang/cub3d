#include "../../includes/cub3d.h"

// hit the wall -> stop  , not conituning
// if not hit the all, update positions.

bool	can_player_move_to(t_game *game, double next_x, double next_y)
{
	printf("next step player at %f %f \n", next_x, next_y);
	printf("int pos_x = %d int pos_y = %d\n", (int)next_x, (int)next_y);
	printf("grid is %c\n", game->map.grid[(int)next_y][(int)next_x]);
	if (game->map.grid[(int)next_y][(int)next_x] == '1'
		|| next_y >= (double)(game->map.height - 1) || next_y <= 0
		|| next_x >= (double)(game->map.width - 1) || next_x <= 0)
	{
		printf("i'm at %d %d, %f\
			%f i hit a wall,i should stop at eh first collisoin point\n",
				(int)game->player.pos_x,
				(int)game->player.pos_y,
				game->player.pos_x,
				game->player.pos_y);
		return (false);
	}
	return (true);
}