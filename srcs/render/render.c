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

void	update_game(t_game *game)
{
	// update player
}

void	render_game(t_game *game)
{
}

int	game_loop(t_game *game)
{
	// handle_input(game);
	update_game(game);
	// 	clear_iamge(game);
	render_game(game);
	// 	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}