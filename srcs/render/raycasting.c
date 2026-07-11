#include "../../includes/cub3d.h"

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
	int color;
	int drawStart;
	int drawEnd;
	// double oldDirX;
	// double oldPlaneX;
	// double oldDirX;
	// double oldPlaneX;
	// double planeX;
	double cameraX;
	// double frameTime;
	// double moveSpeed;
	// double rotSpeed;
	for (int x = 0; x < WIN_W; x++)
	{
		// calculate ray position and direction
		cameraX = 2 * x / (double)WIN_W - 1;
		// x-coordinate in camera space
		rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
		// which box of the map we're in
		mapX = (int)(game->player.pos_x);
		mapY = (int)(game->player.pos_y);
		// length of ray from current position to next x or y-side
		// length of ray from one x or y-side to next x or y-side
		// these are derived as:
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		// which can be simplified to abs(|rayDir|
		//	/ rayDirX) and abs(|rayDir| / rayDirY)
		// where |rayDir| is the length of the vector (rayDirX,
		//	rayDirY). Its length,
		// unlike (dirX, dirY) is not 1, however this does not matter,
		//	only the
		// ratio between deltaDistX and deltaDistY matters,
		//	due to the way the DDA
		// stepping further below works. So the values can be computed as below.
		// Division through zero is prevented,
		// even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
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
			if (game->map.grid[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		// hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		// This can be computed as (mapX - posX + (1 - stepX) / 2)
		//	/ rayDirX for side == 0, or same formula with Y
		// for size == 1,
		//	but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		// because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		// steps,
		//	but we subtract deltaDist once because one step more into the wall was taken above.
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		perpWallDist = (sideDistY - deltaDistY);
		// Calculate height of line to draw on screen
		lineHeight = (int)(WIN_H / perpWallDist);
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + WIN_H / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + WIN_H / 2;
		if (drawEnd >= WIN_H)
			drawEnd = WIN_H - 1;
		// choose wall color
		switch (game->map.grid[mapX][mapY])
		{
		case 1:
			color = 0xFF0000;
			break ; // red
					// case 2:
					// 	color = RGB_Green;
					// 	break ; // green
					// case 3:
					// 	color = RGB_Blue;
					// 	break ; // blue
					// case 4:
					// 	color = RGB_White;
					// 	break ; // white
					// default:
					// 	color = RGB_Yellow;
					// 	break ; // yellow
		}
		// give x and y sides different brightness
		if (side == 1)
		{
			color = color / 2;
		}
		// draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		draw_line(&game->img, x, drawStart, x, drawEnd, color);
	}
}