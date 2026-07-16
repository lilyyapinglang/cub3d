/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:32 by ylang             #+#    #+#             */
/*   Updated: 2026/07/16 19:46:43 by ylang            ###   ########.fr       */
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
	game->ray.deltaDistX = (game->ray.rayDirX == 0) ? 1e30 : fabs(1
			/ game->ray.rayDirX);
	game->ray.deltaDistY = (game->ray.rayDirY == 0) ? 1e30 : fabs(1
			/ game->ray.rayDirY);
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

// Calculate height of line to draw on screen
// calculate lowest and highest pixel to fill in current stripe
void	calculate_strip(t_game *game, int pitch)
{
	if (game->ray.side == 0)
		game->ray.perpWallDist = (game->ray.sideDistX - game->ray.deltaDistX);
	else
		game->ray.perpWallDist = (game->ray.sideDistY - game->ray.deltaDistY);
	game->ray.lineHeight = (int)(WIN_H / game->ray.perpWallDist);
	game->ray.drawStart = -game->ray.lineHeight / 2 + WIN_H / 2 + pitch;
	if (game->ray.drawStart < 0)
		game->ray.drawStart = 0;
	game->ray.drawEnd = game->ray.lineHeight / 2 + WIN_H / 2 + pitch;
	if (game->ray.drawEnd >= WIN_H)
		game->ray.drawEnd = WIN_H - 1;
}

// where exactly the wall was hit
double	get_wall_hit_pos(t_game *game)
{
	double	wall_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos_y + game->ray.perpWallDist
			* game->ray.rayDirY;
	else
		wall_x = game->player.pos_x + game->ray.perpWallDist
			* game->ray.rayDirX;
	wall_x -= floor((wall_x));
	return (wall_x);
}

void	draw_texture_by_pixel(t_game *game, int pitch, int texNum, int x)
{
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned int	color;

	tex_x = (int)(get_wall_hit_pos(game) * (double)game->tex->width);
	if (game->ray.side == 0 && game->ray.rayDirX > 0)
		tex_x = game->tex->width - tex_x - 1;
	if (game->ray.side == 1 && game->ray.rayDirY < 0)
		tex_x = game->tex->width - tex_x - 1;
	step = 1.0 * game->tex->height / game->ray.lineHeight;
	tex_pos = (game->ray.drawStart - pitch - WIN_H / 2 + game->ray.lineHeight
			/ 2) * step;
	for (int y = game->ray.drawStart; y < game->ray.drawEnd; y++)
	{
		tex_y = (int)tex_pos & (game->tex->height - 1);
		tex_pos += step;
		color = *(int *)(game->tex[texNum].img.addr + tex_y
				* game->tex[texNum].img.line_length + tex_x
				* (game->tex[texNum].img.bits_per_pixel / 8));
		if (game->ray.side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&game->img, x, y, color);
	}
}

// texturing calculations
int	texture_calculations(t_game *game)
{
	int	tex_num;

	if (game->ray.side == 0)
	{
		if (game->ray.rayDirX > 0)
			tex_num = WEST_TEX;
		else
			tex_num = EAST_TEX;
	}
	else
	{
		if (game->ray.rayDirY > 0)
			tex_num = NORTH_TEX;
		else
			tex_num = SOUTH_TEX;
	}
	return (tex_num);
}

void	raycasting(t_game *game)
{
	int	pitch;
	int	tex_num;
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray_params(x, game);
		cal_step_n_sidedist(game);
		perform_dda(game);
		pitch = 100;
		calculate_strip(game, pitch);
		tex_num = texture_calculations(game);
		draw_texture_by_pixel(game, pitch, tex_num, x);
		x++;
	}
}
