#include "../../includes/cub3d.h"

/*
 every frame

 clear image
 cast rays
 draw walls with put_pixels()
 draw floor/ceiling
 mlx_put_image_to_window()

*/

/* for every screen column
	x from 0 - width
	cast ray -> hit wall - > calculate distance -> draw vertica lines


*/

void	raycsting(t_game *game, int x)
{
}

void	render(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		raycasting(game, x);
	}
}

/*draw walls ?? */

void	draw_walls(void)
{
	for (y = wall_start_y, y < wall_end_y; y++)
	{
		put_pixel(...);
	}
}

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
