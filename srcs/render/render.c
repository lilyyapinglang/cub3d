/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:29 by ylang             #+#    #+#             */
/*   Updated: 2026/07/16 19:38:23 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 for every frame
 clear image
 cast rays
 draw walls with put_pixels()
 draw floor/ceiling
 mlx_put_image_to_window()
*/

void	clear_image(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	handle_input(t_game *game)
{
	if (game->keys.key_w)
		move_forward(game);
	if (game->keys.key_s)
		move_backward(game);
	if (game->keys.key_a)
		move_left(game);
	if (game->keys.key_d)
		move_right(game);
	if (game->keys.key_left)
		rotate_left(game);
	if (game->keys.key_right)
		rotate_right(game);
}

// last step:draw ui , later， FPS: 60 etc 武器 血量 子弹数量
void	render_game(t_game *game)
{
	clear_image(&game->img, 0);
	draw_floor(game);
	draw_ceiling(game);
	raycasting(game);
	draw_minimap(game);
}

/*
generally the game logic is always: Input -> Update->Render
*/
int	game_loop(t_game *game)
{
	handle_input(game);
	render_game(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
