/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:17:50 by ylang             #+#    #+#             */
/*   Updated: 2026/07/15 19:01:46 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	game->tex[NORTH_TEX].height = 64;
	game->tex[NORTH_TEX].width = 64;
	game->tex[NORTH_TEX].path = "./texture/north64.xpm";
	game->tex[SOUTH_TEX].height = 64;
	game->tex[SOUTH_TEX].width = 64;
	game->tex[SOUTH_TEX].path = "./texture/south64.xpm";
	game->tex[WEST_TEX].height = 64;
	game->tex[WEST_TEX].width = 64;
	game->tex[WEST_TEX].path = "./texture/west64.xpm";
	game->tex[EAST_TEX].height = 64;
	game->tex[EAST_TEX].width = 64;
	game->tex[EAST_TEX].path = "./texture/east64.xpm";
	load_all_textures(game);
}

void	set_player_pos_dir(t_game *game, int y, int x, char direction)
{
	game->player.pos_x = (double)x + 0.5;
	game->player.pos_y = (double)y + 0.5;
	if (direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
}

void	set_player_plane_dir(t_game *game)
{
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
}

void	load_player(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'N')
				set_player_pos_dir(game, y, x, 'N');
			else if (game->map.grid[y][x] == 'S')
				set_player_pos_dir(game, y, x, 'S');
			else if (game->map.grid[y][x] == 'W')
				set_player_pos_dir(game, y, x, 'W');
			else if (game->map.grid[y][x] == 'E')
				set_player_pos_dir(game, y, x, 'E');
			x++;
		}
		y++;
	}
	set_player_plane_dir(game);
}

int	fake_game_init(t_game *game)
{
	int			width_pixel;
	int			height_pixel;
	int			screen_width;
	int			screen_height;
	static char	*map[] = {"111111111111", "100N01000001", "111010111101",
			"100010000101", "101111010101", "100000010001", "101111111101",
			"100000000001", "111111111111", NULL};

	// char	*map1[] = {"111111", "100001", "10N001", "100001", "111111", NULL};
	width_pixel = WIN_W;
	height_pixel = WIN_H;
	game->map.grid = map;
	game->map.height = 9;
	game->map.width = 12;
	load_player(game);
	// printf("posx %f, poxy %f, dir_x %f, dir_y %f, plane_x %f, plane_y %f\n",
	// 	game->player.pos_x, game->player.pos_y, game->player.dir_x,
	// 	game->player.dir_y, game->player.plane_x, game->player.plane_y);
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
	// initiate a big image;
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
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
