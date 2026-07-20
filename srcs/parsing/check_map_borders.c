/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:57 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 16:23:58 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_player_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static int	check_cell(t_game *game, int y, int x)
{
	if (y == 0 || y == game->map.height - 1)
		return (err_msg("", ERR_MAP_OPEN, 1));
	if (x == 0 || x == game->map.width - 1)
		return (err_msg("", ERR_MAP_OPEN, 1));
	if (game->map.grid[y - 1][x] == ' ')
		return (err_msg("", ERR_MAP_OPEN, 1));
	if (game->map.grid[y + 1][x] == ' ')
		return (err_msg("", ERR_MAP_OPEN, 1));
	if (game->map.grid[y][x - 1] == ' ')
		return (err_msg("", ERR_MAP_OPEN, 1));
	if (game->map.grid[y][x + 1] == ' ')
		return (err_msg("", ERR_MAP_OPEN, 1));
	return (0);
}

int	check_borders(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_player_char(game->map.grid[y][x]))
			{
				if (check_cell(game, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map_size(t_game *game)
{
	if (game->map.height < 3 || game->map.width < 3)
		return (err_msg("", ERR_MAP_SIZE, 1));
	return (0);
}
