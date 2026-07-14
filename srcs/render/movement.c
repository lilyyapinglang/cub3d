
#include "../../includes/cub3d.h"

// on W , move forward i nthe direction you're facing
// newPos=pos+direction×speed

void	move_forward(t_game *game)
{
	double	next_x;
	double	next_y;

	printf("plane = (%f, %f)\n", game->player.plane_x, game->player.plane_y);
	next_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	next_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	// in loop, stop until detected release event,
	// printf("facing dir :  %f  %f \n", game->player.dir_x,
	// game->player.dir_y);
	// if (check_hit_wall(game))
	// 	return ;
	printf("next = (%f, %f)\n", next_x, next_y);
	if (can_player_move_to(game, next_x, next_y))
	{
		game->player.pos_x = next_x;
		game->player.pos_y = next_y;
	}
	// printf("moving forward to : %f %f\n", game->player.pos_x,
	// 	game->player.pos_y);
	// printf("\n");
}
// on S , move backaards.
// newPos = pos - direction * speed
void	move_backward(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	next_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	// printf("facing dir :  %f  %f \n", game->player.dir_x,
	// game->player.dir_y);
	if (can_player_move_to(game, next_x, game->player.pos_y))
		game->player.pos_x = next_x;
	if (can_player_move_to(game, game->player.pos_x, next_y))
		game->player.pos_y = next_y;
}

// on A, move left, (perpendicular to the facing direction) ?
void	move_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
	next_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	if (can_player_move_to(game, next_x, next_y))
	{
		game->player.pos_x = next_x;
		game->player.pos_y = next_y;
	}
}

// on D, move right (perpendicular to the facing direction)

void	move_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
	next_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	if (can_player_move_to(game, next_x, next_y))
	{
		game->player.pos_x = next_x;
		game->player.pos_y = next_y;
	}
	printf("posx %f, posy %f, dirx %f, diry %f, planex %f, planey %f\n",
		game->player.pos_x, game->player.pos_y, game->player.dir_x,
		game->player.dir_y, game->player.plane_x, game->player.plane_y);
	printf("\n");
}

// on left arraow,  rorate camera counterclock wise,
//? ? ? need to muptiple by a matrix
/*
to rotate  this point by an angle 𝛼, we use the 2D rotation matrix:
*/
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = old_dir_x * cos(-ROTATION_SPEED) - game->player.dir_y
		* sin(-ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) + game->player.dir_y
		* cos(-ROTATION_SPEED);
	game->player.plane_x = old_plane_x * cos(-ROTATION_SPEED)
		- game->player.plane_y * sin(-ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player.plane_y * cos(-ROTATION_SPEED);
	printf("rotating left, posx %f, posy %f, dirx %f, diry %f, planex %f,planey\
				% f\n ",
			game->player.pos_x,
			game->player.pos_y,
			game->player.dir_x,
			game->player.dir_y,
			game->player.plane_x,
			game->player.plane_y);
	printf("\n");
}

// on right arrow, rotate camera clockwise, dir rotate, plane rotate too
void	rotate_right(t_game *game)
{
	double old_dir_x = game->player.dir_x;
	double old_plane_x = game->player.plane_x;
	game->player.dir_x = old_dir_x * cos(ROTATION_SPEED) - game->player.dir_y
		* sin(ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir_y
		* cos(ROTATION_SPEED);
	game->player.plane_x = old_plane_x * cos(ROTATION_SPEED)
		- game->player.plane_y * sin(ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(ROTATION_SPEED)
		+ game->player.plane_y * cos(ROTATION_SPEED);
	printf("rotating right, posx %f, posy %f, dirx %f, diry %f, planex\
		%f,planey %f\n ",
			game->player.pos_x,
			game->player.pos_y,
			game->player.dir_x,
			game->player.dir_y,
			game->player.plane_x,
			game->player.plane_y);
	printf("\n");
}