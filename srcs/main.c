#include "../includes/cub3d.h"

static int	on_key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		graceful_exit(game, 0);
	return (0);
}

static void	set_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, on_key_press, game);
	mlx_hook(game->win, ClientMessage, NoEventMask, handle_exit, game);
}

// static void	init_imgs_ptrs(t_imgs *imgs)
// {
// 	imgs->wall_img = NULL;
// 	imgs->floor_img = NULL;
// 	imgs->collectible_img = NULL;
// 	imgs->exit_img = NULL;
// 	imgs->player_img = NULL;
// }

int	game_init(t_game *game)
{
	int		width_pixel;
	int		height_pixel;
	int		screen_width;
	int		screen_height;
	char	*map[] = {"111111", "100001", "10N001", "100001", "111111", NULL};

	game->map.grid = map;
	// game.grid = map;
	game->player.player_pos_x = 2.5;
	game->player.player_pos_y = 2.5;
	game->floor = 0x00FF00;
	game->ceiling = 0x87CEEB;
	game->win = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_out("mlx_init failed"), -1);
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (width_pixel <= 0 || height_pixel <= 0 || width_pixel > screen_width
		|| height_pixel > screen_height)
		return (error_out("out of screen size"), -1);
	game->win = mlx_new_window(game->mlx, width_pixel, height_pixel,
			"Welcome to Magic Game!");
	if (!game->win)
		return (error_out("mlx_new_window failed"), -1);
	imgs_init(game);
}

/*
MLX initialization
drawing pixels
raycasting
movement
collision
keyboard handling
*/
int	main(int argc, char **argv)
{
	t_game	cub;

	(void)argv;
	if (argc != 2)
		return (err_msg("", ERR_USAGE, 1));
	init_all(&cub);
	init_mlx(&cub);
	set_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
