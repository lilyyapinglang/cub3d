#include "../../includes/cub3d.h"

int	render_next_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game->is_redraw_needed)
		return (0);
	draw_full_map(game);
	game->is_redraw_needed = 0;
	return (0);
}

int	on_expose(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	game->is_redraw_needed = 1;
	return (0);
}

int	on_key(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == XK_Escape)
		return (destroy_all(game), 0);
	else if (keycode == XK_w || keycode == XK_Up)
		move_and_see(game, game->map.player_x_pos - 1, game->map.player_y);
	else if (keycode == XK_s || keycode == XK_Down)
		move_and_see(game, game->map.player_x + 1, game->map.player_y);
	else if (keycode == XK_a || keycode == XK_Left)
		move_and_see(game, game->map.player_x, game->map.player_y - 1);
	else if (keycode == XK_d || keycode == XK_Right)
		move_and_see(game, game->map.player_x, game->map.player_y + 1);
	return (0);
}

int	on_destroy(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	destroy_all(game);
	return (0);
}
