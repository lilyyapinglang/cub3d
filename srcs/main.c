#include "../includes/cub3d.h"

static void	set_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, on_key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, on_key_relase, game);
	mlx_hook(game->win, ClientMessage, NoEventMask, handle_exit, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

// void	init_fake_textures(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	i;

// 	for (i = 0; i < 4; i++)
// 	{
// 		game->tex[i].width = 64;
// 		game->tex[i].height = 64;
// 		game->tex[i].pixels = malloc(sizeof(uint32_t) * 64 * 64);
// 	}
// 	for (y = 0; y < 64; y++)
// 	{
// 		for (x = 0; x < 64; x++)
// 		{
// 			game->tex[0].pixels[y * 64 + x] = (((x / 8) + (y / 8))
// 					% 2) ? 0xFF0000 : 0x880000;
// 			game->tex[1].pixels[y * 64 + x] = (((x / 8) + (y / 8))
// 					% 2) ? 0x00FF00 : 0x008800;
// 			game->tex[2].pixels[y * 64 + x] = (((x / 8) + (y / 8))
// 					% 2) ? 0x0000FF : 0x000088;
// 			game->tex[3].pixels[y * 64 + x] = (((x / 8) + (y / 8))
// 					% 2) ? 0xFFFF00 : 0x888800;
// 		}
// 	}
// }

void	init_fake_texture_from_file(t_game *game)
{
	game->tex[0].height = 64;
	game->tex[0].width = 64;
	game->tex[0].path = "./texture/north64.xpm";
	game->tex[1].height = 64;
	game->tex[1].width = 64;
	game->tex[1].path = "./texture/south64.xpm";
	game->tex[2].height = 64;
	game->tex[2].width = 64;
	game->tex[2].path = "./texture/east64.xpm";
	game->tex[3].height = 64;
	game->tex[3].width = 64;
	game->tex[3].path = "./texture/west64.xpm";
	load_all_textures(game);
}

int	fake_game_init(t_game *game)
{
	int			width_pixel;
	int			height_pixel;
	int			screen_width;
	int			screen_height;
	static char	*map[] = {"111111111111", "1N0001000001", "111010111101",
			"100010000101", "101111010101", "100000010001", "101111111101",
			"100000000001", "111111111111", NULL};

	// char	*map1[] = {"111111", "100001", "10N001", "100001", "111111", NULL};
	width_pixel = WIN_W;
	height_pixel = WIN_H;
	game->map.grid = map;
	game->map.height = 9;
	game->map.width = 12;
	game->player.pos_x = 1.5;
	game->player.pos_y = 1.5;
	// FOV = 66 degrees;
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	game->floor = 0xFFC5D3;   // LIGHT PINK
	game->ceiling = 0x90D5FF; // LIGHT BLUE
	game->win = NULL;
	game->mlx = mlx_init();
	game->keys.key_a = false;
	game->keys.key_d = false;
	game->keys.key_s = false;
	game->keys.key_w = false;
	game->keys.key_left = false;
	game->keys.key_right = false;
	init_fake_texture_from_file(game);
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
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	// init_fake_textures(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	// if (argc != 2)
	// 	return (err_msg("", ERR_USAGE, 1));
	(void)argc;
	(void)argv;
	// init_all(&game);
	// init_mlx(&game);
	// if (parse_file(&game, argv))
	// 	return (1);
	fake_game_init(&game);
	// 1. keyboard events 2. mouse events 3. a part of window needs to be redrawn (expose)
	set_hooks(&game);
	// to receive events , mlx_loop is needed, to initiade the loop
	mlx_loop(game.mlx);
	return (0);
}
