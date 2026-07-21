/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 19:54:35 by ylang             #+#    #+#             */
/*   Updated: 2026/07/21 15:34:54 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)pixel = color;
	}
}

void	draw_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&game->img, x, y, game->ceiling);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game)
{
	int	x;
	int	y;

	y = WIN_H / 2;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&game->img, x, y, game->floor);
			x++;
		}
		y++;
	}
}
