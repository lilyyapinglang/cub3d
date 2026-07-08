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

int	draw_line(void *mlx, void *win, int begin_x, int begin_y, int end_x,
		int end_y, int color)
{
	double	delta_x;
	double	delta_y;
	int		number_of_pixels_to_draw;
	double	pixel_x;
	double	pixel_y;

	delta_x = end_x - begin_x;
	delta_y = end_y - begin_y;
	number_of_pixels_to_draw = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= number_of_pixels_to_draw;
	delta_y /= number_of_pixels_to_draw;
	pixel_x = begin_x;
	pixel_y = begin_y;
	while (number_of_pixels_to_draw)
	{
		mlx_pixel_put(mlx, win, pixel_x, pixel_y, color);
		// put_pixel(&img, WIN_W / 2, WIN_H / 2, 0xFF0000);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--number_of_pixels_to_draw;
	}
	return (0);
}

void	draw_ceiling(t_game *game, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, game->ceiling);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y >= WIN_H / 2 && y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, game->floor);
			x++;
		}
		y++;
	}
}
