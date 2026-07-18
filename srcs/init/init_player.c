/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 00:00:00 by ylang             #+#    #+#             */
/*   Updated: 2026/07/18 00:00:00 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
