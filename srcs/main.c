#include "../includes/cub3d.h"
#include <math.h>

static void	set_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, on_key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, on_key_relase, game);
	mlx_hook(game->win, ClientMessage, NoEventMask, handle_exit, game);
	// mlx_loop_hook(game->win, render_next_frame, game);
}

int	fake_game_init(t_game *game)
{
	int		width_pixel;
	int		height_pixel;
	int		screen_width;
	int		screen_height;
	char	*map[] = {"111111", "100001", "10N001", "100001", "111111", NULL};

	width_pixel = WIN_W;
	height_pixel = WIN_H;
	game->map.grid = map;
	game->map.height = 5;
	game->map.width = 6;
	game->player.pos_x = 2.5;
	game->player.pos_y = 2.5;
	// FOV = 66 degrees;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	game->floor = 0x00FF00;
	game->ceiling = 0x87CEEB;
	game->win = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("mlx_init failed"), -1);
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (width_pixel <= 0 || height_pixel <= 0 || width_pixel > screen_width
		|| height_pixel > screen_height)
		return (printf("out of screen size"), -1);
	game->win = mlx_new_window(game->mlx, width_pixel, height_pixel,
			"Welcome to Magic Game!");
	if (!game->win)
		return (printf("mlx_new_window failed"), -1);
	// imgs_init(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_img	img;

	// if (argc != 2)
	// 	return (err_msg("", ERR_USAGE, 1));
	(void)argc;
	(void)argv;
	// init_all(&game);
	// if (parse_file(&game, argv))
	// 	return (1);
	fake_game_init(&game);
	img.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	// put_pixel(&img, WIN_W / 2, WIN_H / 2, 0xFF0000);
	// draw_line(&img, WIN_W / 2, 0, WIN_W / 2, WIN_H, 0xFF0000);
	draw_rectangle(&img, WIN_W / 2, 0, WIN_W, WIN_H, 0xFF0000);
	// draw_ceiling(&game, &img);
	// draw_floor(&game, &img);
	mlx_put_image_to_window(game.mlx, game.win, img.img, 0, 0);
	// 1. keyboard events 2. mouse events 3. a part of window needs to be redrawn (expose)
	set_hooks(&game);
	// to receive events , mlx_loop is needed
	mlx_loop(game.mlx);
	//  init_mlx(&game);
	//  mlx_loop_hook(game.mlx, game_loop, game);
	return (0);
}
