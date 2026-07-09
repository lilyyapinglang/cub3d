
#include "../../includes/cub3d.h"

// on W , move forward i nthe direction you're facing

void	move_forward(t_game *game)
{
	// in loop, stop until detected release event,
	printf("facing dir :  %f  %f \n", game->player.dir_x, game->player.dir_y);
	game->player.pos_x += game->player.dir_x * MOVE_SPEED;
	game->player.pos_y += game->player.dir_y * MOVE_SPEED;
	printf("moving forward to : %f %f\n", game->player.pos_x,
		game->player.pos_y);
}
// on S , move backaards.

void	move_backward(t_game *game)
{
	printf("facing dir :  %f  %f \n", game->player.dir_x, game->player.dir_y);
	game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
	game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
	printf("moving backward to : %f %f\n", game->player.pos_x,
		game->player.pos_y);
}

// on A, move left, (perpendicular to the facing direction) ?
void	move_left(t_game *game)
{
	printf("facing dir :  %f  %f \n", game->player.dir_x, game->player.dir_y);
	game->player.pos_x += game->player.plane_x * MOVE_SPEED;
	game->player.pos_y += game->player.plane_y * MOVE_SPEED;
	printf("moving left to : %f %f\n", game->player.pos_x, game->player.pos_y);
}

// on D, move right (perpendicular to the facing direction)

void	move_right(t_game *game)
{
	printf("facing dir :  %f  %f \n", game->player.dir_x, game->player.dir_y);
	game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
	game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
	printf("moving right to : %f %f\n", game->player.pos_x, game->player.pos_y);
}

// on left arraow,  rorate camera counterclock wise,
//? ? ? need to muptiple by a matrix
/*
to rotate  this point by an angle 𝛼, we use the 2D rotation matrix:
*/
void	rotate_left(t_game *game)
{
	// change the dir and plane
	printf("before left rotate, facing dir :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
	printf("before left rotate,facing plane :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
	game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED)
		- game->player.dir_y * sin(ROTATION_SPEED);
	game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED)
		+ game->player.dir_y * sin(ROTATION_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED)
		- game->player.plane_y * sin(ROTATION_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED)
		+ game->player.plane_y * sin(ROTATION_SPEED);
	printf("after left rotate, facing dir :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
	printf("after left rotate, facing plane :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
}
// on right arrow, rotate camera clockwise
void	rotate_right(t_game *game)
{
	// change the dir and plane
	printf("before right rotate, facing dir :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
	printf("before right rotate,facing plane :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
	game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED)
		+ game->player.dir_y * sin(ROTATION_SPEED);
	game->player.dir_x = -game->player.dir_x * sin(ROTATION_SPEED)
		+ game->player.dir_y * cos(ROTATION_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED)
		+ game->player.plane_y * sin(ROTATION_SPEED);
	game->player.plane_x = -game->player.plane_x * sin(ROTATION_SPEED)
		+ game->player.plane_y * cos(ROTATION_SPEED);
	printf("after right rotate, facing dir :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
	printf("after rightrotate, facing plane :  %f  %f \n", game->player.dir_x,
		game->player.dir_y);
}