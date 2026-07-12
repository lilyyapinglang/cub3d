
#include "../../includes/cub3d.h"

int	on_key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		graceful_exit(game, 0);
	if (key == XK_w)
		game->keys.key_w = true;
	if (key == XK_s)
		game->keys.key_s = true;
	if (key == XK_a)
		game->keys.key_a = true;
	if (key == XK_d)
		game->keys.key_d = true;
	if (key == XK_Left)
		game->keys.key_left = true;
	if (key == XK_Right)
		game->keys.key_right = true;
	return (0);
}

int	on_key_relase(int key, t_game *game)
{
	if (key == XK_w)
		game->keys.key_w = false;
	if (key == XK_s)
		game->keys.key_s = false;
	if (key == XK_a)
		game->keys.key_a = false;
	if (key == XK_d)
		game->keys.key_d = false;
	if (key == XK_Left)
		game->keys.key_left = false;
	if (key == XK_Right)
		game->keys.key_right = false;
	return (0);
}

// window is changed, covered , etc, where redraw is needed
// another window was covering yours
// you minimized then restored it
// the OS requests a redraw
int	on_expose(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	(void)game;
	// game->is_redraw_needed = 1;
	return (0);
}
