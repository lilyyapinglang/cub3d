
#include "../../includes/cub3d.h"

int	on_key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		graceful_exit(game, 0);
	if (key == XK_W || XK_w)
		move_forward(game);
	if (key == XK_S || XK_s)
		move_backward(game);
	if (key == XK_A || key == XK_a)
		move_left(game);
	if (key == XK_D || XK_d)
		move_right(game);
	if (key == XK_Left)
		rotate_left(game);
	if (key == XK_Right)
		rotate_right(game);
	return (0);
}

int	on_key_relase(int key, t_game *game)
{
	(void)key;
	(void)game;
	// release key will stop moving or rotating, how to define ?
	// 	if (key == XK_W || XK_w)
	// 		stop_move_forward(game);
	// 	if (key == XK_S || XK_s)
	// 		stop_move_backward(game);
	// 	if (key == XK_A || key == XK_a)
	// 		stop_move_left(game);
	// 	if (key == XK_D || XK_d)
	// 		stop_move_right(game);
	// 	if (key = XK_Left)
	// 		stop_rotate_left(game);
	// 	if (key == XK_Right)
	// 		stop_rorate_right(game);
	return (0);
}

// window is changed, covered , etc, where redraw is needed
int	on_expose(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	// game->is_redraw_needed = 1;
	return (0);
}
