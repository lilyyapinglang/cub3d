/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:32 by ylang             #+#    #+#             */
/*   Updated: 2026/07/16 18:04:45 by ylang            ###   ########.fr       */
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
	double	cameraX;

	// calculate ray position and direction
	cameraX = 2 * x / (double)WIN_W - 1;
	// x-coordinate in camera space
	game->ray.rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
	game->ray.rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
	// which box of the map we're in
	game->ray.mapX = (int)(game->player.pos_x);
	game->ray.mapY = (int)(game->player.pos_y);
	game->ray.deltaDistX = (game->ray.rayDirX == 0) ? 1e30 : fabs(1
			/ game->ray.rayDirX);
	game->ray.deltaDistY = (game->ray.rayDirY == 0) ? 1e30 : fabs(1
			/ game->ray.rayDirY);
	// what direction to step in x or y-direction (either +1 or -1)
	game->ray.hit = 0;  // was there a wall hit?
	game->ray.side = 0; // was a NS or a EW wall hit?
						// calculate step and initial sideDist
}

// set ray related params like stepx, stepy, sideDistX, deltaDistX, etc.
void	cal_step_n_sideDist(t_game *game)
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
		// jump to next map square, either in x-direction,
		// or in y - direction
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
		// Check if ray has hit a wall
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
	// Calculate height of line to draw on screen
	game->ray.lineHeight = (int)(WIN_H / game->ray.perpWallDist);
	// calculate lowest and highest pixel to fill in current stripe
	game->ray.drawStart = -game->ray.lineHeight / 2 + WIN_H / 2 + pitch;
	if (game->ray.drawStart < 0)
		game->ray.drawStart = 0;
	game->ray.drawEnd = game->ray.lineHeight / 2 + WIN_H / 2 + pitch;
	if (game->ray.drawEnd >= WIN_H)
		game->ray.drawEnd = WIN_H - 1;
}

double	get_wall_hit_pos(t_game *game)
{
	double wallX; // where exactly the wall was hit
	if (game->ray.side == 0)
		wallX = game->player.pos_y + game->ray.perpWallDist * game->ray.rayDirY;
	else
		wallX = game->player.pos_x + game->ray.perpWallDist * game->ray.rayDirX;
	wallX -= floor((wallX));
	return (wallX);
}
void	draw_texture_by_pixel(t_game *game, int pitch, int texNum, int x)
{
	int				texX;
	double			step;
	double			texPos;
	int				texY;
	unsigned int	color;

	double wallX; // where exactly the wall was hit
	if (game->ray.side == 0)
		wallX = game->player.pos_y + game->ray.perpWallDist * game->ray.rayDirY;
	else
		wallX = game->player.pos_x + game->ray.perpWallDist * game->ray.rayDirX;
	wallX -= floor((wallX));
	texX = (int)(wallX * (double)game->tex->width);
	if (game->ray.side == 0 && game->ray.rayDirX > 0)
		texX = game->tex->width - texX - 1;
	if (game->ray.side == 1 && game->ray.rayDirY < 0)
		texX = game->tex->width - texX - 1;
	step = 1.0 * game->tex->height / game->ray.lineHeight;
	texPos = (game->ray.drawStart - pitch - WIN_H / 2 + game->ray.lineHeight
			/ 2) * step;
	for (int y = game->ray.drawStart; y < game->ray.drawEnd; y++)
	{
		texY = (int)texPos & (game->tex->height - 1);
		texPos += step;
		color = *(int *)(game->tex[texNum].data + texY
				* game->tex[texNum].line_len + texX * (game->tex[texNum].bpp
					/ 8));
		if (game->ray.side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&game->img, x, y, color);
	}
}

int	texture_calculations(t_game *game)
{
	int	texNum;

	if (game->ray.side == 0)
	{
		if (game->ray.rayDirX > 0)
			texNum = WEST_TEX;
		else
			texNum = EAST_TEX;
	}
	else
	{
		if (game->ray.rayDirY > 0)
			texNum = NORTH_TEX;
		else
			texNum = SOUTH_TEX;
	}
	return (texNum);
}

void	raycasting(t_game *game)
{
	int	pitch;
	int	texNum;
	int	x;

	// int	wallX;
	x = 0;
	while (x < WIN_W)
	{
		init_ray_params(x, game);
		cal_step_n_sideDist(game);
		perform_dda(game);
		pitch = 100;
		calculate_strip(game, pitch);
		// texturing calculations
		texNum = texture_calculations(game);
		// wallX = get_wall_hit_pos(game);
		draw_texture_by_pixel(game, pitch, texNum, x);
		x++;
	}
}
