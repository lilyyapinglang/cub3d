/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:32 by ylang             #+#    #+#             */
/*   Updated: 2026/07/15 18:55:17 by ylang            ###   ########.fr       */
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

void	raycasting(t_game *game)
{
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int lineHeight;
	int drawStart;
	int drawEnd;
	double cameraX;
	int pitch;

	int texX;
	double step;
	double texPos;
	int texY;
	unsigned int color;
	int texNum;

	int x = 0;
	while (x < WIN_W)
	{
		// calculate ray position and direction
		cameraX = 2 * x / (double)WIN_W - 1;
		// x-coordinate in camera space
		rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
		// which box of the map we're in
		mapX = (int)(game->player.pos_x);
		mapY = (int)(game->player.pos_y);

		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		// what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?
		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.pos_y) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction,
			// or in y - direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (game->map.grid[mapY][mapX] == '1')
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		// Calculate height of line to draw on screen
		lineHeight = (int)(WIN_H / perpWallDist);

		pitch = 100;
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + WIN_H / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + WIN_H / 2 + pitch;
		if (drawEnd >= WIN_H)
			drawEnd = WIN_H - 1;
		// texturing calculations
		if (side == 0)
		{
			if (rayDirX > 0)
				texNum = WEST_TEX; // 3west
			else
				texNum = EAST_TEX; // 2esst
		}
		else
		{
			if (rayDirY > 0)
				texNum = NORTH_TEX; // 0south
			else
				texNum = SOUTH_TEX; // 1north
		}
		// 1 subtracted from it so that texture 0 can be used!
		// calculate value of wallX
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = game->player.pos_y + perpWallDist * rayDirY;
		else
			wallX = game->player.pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		// x coordinate on the texture
		texX = (int)(wallX * (double)game->tex->width);
		if (side == 0 && rayDirX > 0)
			texX = game->tex->width - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = game->tex->width - texX - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		step = 1.0 * game->tex->height / lineHeight;
		// Starting texture coordinate
		texPos = (drawStart - pitch - WIN_H / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight
			//	- 1) in case of overflow
			texY = (int)texPos & (game->tex->height - 1);
			texPos += step;
			// color = game->tex[texNum].pixels[texY * game->tex[texNum].width
			// 	+ texX];
			int offset = texY * game->tex[texNum].line_len + texX
				* (game->tex[texNum].bpp / 8);
			color = *(int *)(game->tex[texNum].data + offset);

			// make color darker for y-sides: R,
			// G and B byte each divided through two with a "shift" and an "and" if (side == 1) color = (color >> 1) & 8355711;
			put_pixel(&game->img, x, y, color);
		}
		x++;
	}
}