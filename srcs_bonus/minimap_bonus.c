/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:38 by ylang             #+#    #+#             */
/*   Updated: 2026/07/21 15:29:39 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_tile(t_game *game, int y, int x, bool filled)
{
	t_point	point1;
	t_point	point2;

	point1 = (t_point){x * TILE_SIZE, y * TILE_SIZE};
	point2 = (t_point){(x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE};
	if (filled)
		draw_filled_rectangle(&game->img, point1, point2, 0xff0000);
	draw_rectangle(&game->img, point1, point2, 0xFFA500);
}

void	draw_map_tiles(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == '1')
				draw_tile(game, i, j, true);
			else
				draw_tile(game, i, j, false);
			j++;
		}
		i++;
	}
}

// green
void	draw_player_n_viewing_direction(t_game *game)
{
	t_point	point1;
	t_point	point2;

	point1 = (t_point){game->player.pos_x * TILE_SIZE - 2.5, game->player.pos_y
		* TILE_SIZE - 2.5};
	point2 = (t_point){game->player.pos_x * TILE_SIZE + 2.5, game->player.pos_y
		* TILE_SIZE + 2.5};
	draw_filled_rectangle(&game->img, point1, point2, 0x00ff00);
	point1 = (t_point){game->player.pos_x * TILE_SIZE, game->player.pos_y
		* TILE_SIZE};
	point2 = (t_point){(game->player.pos_x + game->player.dir_x) * TILE_SIZE,
		(game->player.pos_y + game->player.dir_y) * TILE_SIZE};
	draw_line(&game->img, point1, point2, 0x00ff00);
	point1 = (t_point){(game->player.pos_x + game->player.dir_x) * TILE_SIZE
		- 2.5, (game->player.pos_y + game->player.dir_y) * TILE_SIZE - 2.5};
	point2 = (t_point){(game->player.pos_x + game->player.dir_x) * TILE_SIZE
		+ 2.5, (game->player.pos_y + game->player.dir_y) * TILE_SIZE + 2.5};
	draw_filled_rectangle(&game->img, point1, point2, 0xFAFA37);
}

// pink
void	draw_plane_direction(t_game *game)
{
	t_point	start;
	t_point	end;
	t_point	point1;
	t_point	point2;

	start.x = game->player.pos_x;
	start.y = game->player.pos_y;
	end.x = game->player.pos_x + game->player.plane_x;
	end.y = game->player.pos_y + game->player.plane_y;
	point1.x = start.x * TILE_SIZE;
	point1.y = start.y * TILE_SIZE;
	point2.x = end.x * TILE_SIZE;
	point2.y = end.y * TILE_SIZE;
	draw_line(&game->img, point1, point2, 0xFF00FF);
	point1.x = end.x * TILE_SIZE - 2.5;
	point1.y = end.y * TILE_SIZE - 2.5;
	point2.x = end.x * TILE_SIZE + 2.5;
	point2.y = end.y * TILE_SIZE + 2.5;
	draw_filled_rectangle(&game->img, point1, point2, 0xFF00FF);
}

void	draw_minimap(t_game *game)
{
	draw_map_tiles(game);
	draw_player_n_viewing_direction(game);
	draw_plane_direction(game);
}
