/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:32 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 18:42:38 by ylang            ###   ########.fr       */
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

// Calculate height of line to draw on screen
// calculate lowest and highest pixel to fill in current stripe
void	calculate_strip(t_game *game, int pitch)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.side_dist_x
				- game->ray.delta_dist_x);
	else
		game->ray.perp_wall_dist = (game->ray.side_dist_y
				- game->ray.delta_dist_y);
	game->ray.line_height = (int)(WIN_H / game->ray.perp_wall_dist);
	game->ray.draw_start = -game->ray.line_height / 2 + WIN_H / 2 + pitch;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + WIN_H / 2 + pitch;
	if (game->ray.draw_end >= WIN_H)
		game->ray.draw_end = WIN_H - 1;
}

// where exactly the wall was hit
double	get_wall_hit_pos(t_game *game)
{
	double	wall_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos_y + game->ray.perp_wall_dist
			* game->ray.ray_dir_y;
	else
		wall_x = game->player.pos_x + game->ray.perp_wall_dist
			* game->ray.ray_dir_x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

// if (game->ray.side == 1)color = (color >> 1) & 8355711;
void	draw_texture_by_pixel(t_game *game, int pitch, int texNum, int x)
{
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned int	color;

	tex_x = (int)(get_wall_hit_pos(game) * (double)game->tex->width);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		tex_x = game->tex->width - tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		tex_x = game->tex->width - tex_x - 1;
	step = 1.0 * game->tex->height / game->ray.line_height;
	tex_pos = (game->ray.draw_start - pitch - WIN_H / 2 + game->ray.line_height
			/ 2) * step;
	while (game->ray.draw_start < game->ray.draw_end)
	{
		tex_y = (int)tex_pos & (game->tex->height - 1);
		tex_pos += step;
		color = *(int *)(game->tex[texNum].img.addr + tex_y
				* game->tex[texNum].img.line_length + tex_x
				* (game->tex[texNum].img.bits_per_pixel / 8));
		put_pixel(&game->img, x, game->ray.draw_start, color);
		game->ray.draw_start++;
	}
}

// texturing calculations
int	texture_calculations(t_game *game)
{
	int	tex_num;

	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			tex_num = WEST_TEX;
		else
			tex_num = EAST_TEX;
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
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
