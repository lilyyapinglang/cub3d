
#include "../../includes/cub3d.h"

// on W , move forward i nthe direction you're facing

void	move_forward(t_game *game)
{
	// in loop, stop until detected release event,
	game->player.pos_x += game->player.dir_x * MOVE_SPEED;
	game->player.pos_y += game->player.dir_y * MOVE_SPEED;
}
// on S , move backaards.

void	move_backward(t_game *game)
{
	game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
	game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
}

// on A, move left, (perpendicular to the facing direction) ?

void	move_left(t_game *game)
{
	game->player.pos_x += game->player.plane_x * MOVE_SPEED;
	game->player.pos_y += game->player.plane_y * MOVE_SPEED;
}

// on D, move right (perpendicular to the facing direction)

void	move_right(t_game *game)
{
	game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
	game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
}

// on left arraow,  rorate camera counterclock wise,
//? ? ? need to muptiple by a matrix

void	rotate_left(t_game *game)
{
	(void)game;
}
// on right arrow, rotate camera clockwise
void	rotate_right(t_game *game)
{
	(void)game;
}