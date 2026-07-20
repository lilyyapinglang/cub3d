/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_contents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:54 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 16:23:55 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	check_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (!is_valid_char(game->map.grid[y][x]))
				return (err_msg("", ERR_MAP_CHARS, 1));
			x++;
		}
		y++;
	}
	return (0);
}

static int	is_player_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	find_player(t_game *game, int *count)
{
	int	y;
	int	x;

	*count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_player_dir(game->map.grid[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				(*count)++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_player(t_game *game)
{
	int	count;

	find_player(game, &count);
	if (count != 1)
		return (err_msg("", ERR_MAP_PLAYER, 1));
	return (0);
}
