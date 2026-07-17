/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:32 by ylang             #+#    #+#             */
/*   Updated: 2026/07/17 20:19:28 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* for every screen column
	x from 0 - width
	cast ray -> hit wall - > calculate distance -> draw vertica lines
 raycast every column
		↓
	draw wall slice
*/
void	init_ray_params(int x, t_game *game)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_W - 1;
	game->ray.rayDirX = game->player.dir_x + game->player.plane_x * camera_x;
	game->ray.rayDirY = game->player.dir_y + game->player.plane_y * camera_x;
	game->ray.mapX = (int)(game->player.pos_x);
	game->ray.mapY = (int)(game->player.pos_y);
	// if (game == NULL)
	// 	printf("HELLPPPPP\n\n\n\n\n");
	if (game->ray.rayDirX == 0)
		game->ray.deltaDistX = 1e30;
	else
		game->ray.deltaDistX = fabs(1.0 / game->ray.rayDirX);
	// printf("%f,", game->ray.deltaDistY);
	if (game->ray.rayDirY == 0)
		game->ray.deltaDistY = 1e30;
	else
		game->ray.deltaDistY = fabs(1 / game->ray.rayDirY);
	game->ray.hit = 0;
	game->ray.side = 0;
}

// set ray related params like stepx, stepy, sideDistX, deltaDistX, etc.
void	cal_step_n_sidedist(t_game *game)
{
	if (game->ray.rayDirX < 0)
	{
		game->ray.stepX = -1;
		game->ray.sideDistX = (game->player.pos_x - game->ray.mapX)
			* game->ray.deltaDistX;
	}
	else
	{
		game->ray.stepX = 1;
		game->ray.sideDistX = (game->ray.mapX + 1.0 - game->player.pos_x)
			* game->ray.deltaDistX;
	}
	if (game->ray.rayDirY < 0)
	{
		game->ray.stepY = -1;
		game->ray.sideDistY = (game->player.pos_y - game->ray.mapY)
			* game->ray.deltaDistY;
	}
	else
	{
		game->ray.stepY = 1;
		game->ray.sideDistY = (game->ray.mapY + 1.0 - game->player.pos_y)
			* game->ray.deltaDistY;
	}
}

void	perform_dda(t_game *game)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.sideDistX < game->ray.sideDistY)
		{
			game->ray.sideDistX += game->ray.deltaDistX;
			game->ray.mapX += game->ray.stepX;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sideDistY += game->ray.deltaDistY;
			game->ray.mapY += game->ray.stepY;
			game->ray.side = 1;
		}
		if (game->map.grid[game->ray.mapY][game->ray.mapX] == '1')
			game->ray.hit = 1;
	}
}
