/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:17:50 by ylang             #+#    #+#             */
/*   Updated: 2026/07/18 18:58:57 by ylang            ###   ########.fr       */
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

void	init_load_texture_from_file(t_game *game)
{
	game->tex[NORTH_TEX].height = 64;
	game->tex[NORTH_TEX].width = 64;
	game->tex[SOUTH_TEX].height = 64;
	game->tex[SOUTH_TEX].width = 64;
	game->tex[WEST_TEX].height = 64;
	game->tex[WEST_TEX].width = 64;
	game->tex[EAST_TEX].height = 64;
	game->tex[EAST_TEX].width = 64;
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

int	load_data(t_game *game)
{
	load_player(game);
	game->keys.key_a = false;
	game->keys.key_d = false;
	game->keys.key_s = false;
	game->keys.key_w = false;
	game->keys.key_left = false;
	game->keys.key_right = false;
	init_load_texture_from_file(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (err_msg("", ERR_USAGE, 1));
	init_all(&game);
	if (parse_file(&game, argv))
		return (1);
	init_mlx(&game);
	printf("map width is : %d, map height is :%d \n", game.map.width,
		game.map.height);
	printf("tex 0.1.2.3 path %s, %s, %s, %s\n", game.tex[0].path,
		game.tex[1].path, game.tex[2].path, game.tex[2].path);
	load_data(&game);
	// 1. keyboard events 2. mouse events 3. a part of window needs to be redrawn (expose)
	set_hooks(&game);
	// to receive events , mlx_loop is needed, to initiade the loop
	mlx_loop(game.mlx);
	return (0);
}
