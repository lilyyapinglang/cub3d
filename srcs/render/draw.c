/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:43 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 19:55:07 by ylang            ###   ########.fr       */
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

int	draw_line(t_img *img, t_point begin, t_point end, int color)
{
	double	delta_x;
	double	delta_y;
	int		number_of_pixels_to_draw;
	double	pixel_x;
	double	pixel_y;

	delta_x = end.x - begin.x;
	delta_y = end.y - begin.y;
	number_of_pixels_to_draw = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= number_of_pixels_to_draw;
	delta_y /= number_of_pixels_to_draw;
	pixel_x = begin.x;
	pixel_y = begin.y;
	while (number_of_pixels_to_draw)
	{
		put_pixel(img, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--number_of_pixels_to_draw;
	}
	return (0);
}

void	draw_rectangle(t_img *img, t_point point1, t_point point2, int color)
{
	int	point1_x;
	int	point1_y;
	int	point2_x;
	int	point2_y;

	point1_x = point1.x;
	point1_y = point1.y;
	point2_x = point2.x;
	point2_y = point2.y;
	point2.y = point1_y;
	draw_line(img, point1, point2, color);
	point2.x = point1_x;
	point2.y = point2_y;
	draw_line(img, point1, point2, color);
	point1.y = point2_y - 1;
	point2.x = point2_x;
	point2.y = point2_y - 1;
	draw_line(img, point1, point2, color);
	point1.x = point2_x - 1;
	point1.y = point1_y;
	point2.x = point2_x - 1;
	point2.y = point2_y;
	draw_line(img, point1, point2, color);
}

void	draw_filled_rectangle(t_img *img, t_point point1, t_point point2,
		int color)
{
	int	x;
	int	y;

	x = point1.x;
	y = point1.y;
	while (y < point2.y)
	{
		x = point1.x;
		while (x < point2.x)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
