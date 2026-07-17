/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:35 by ylang             #+#    #+#             */
/*   Updated: 2026/07/16 19:38:38 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// on W , move forward in the direction you're facing
// newPos=pos+direction×speed
void	move_forward(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	next_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (can_player_move_to(game, next_x, game->player.pos_y))
		game->player.pos_x = next_x;
	if (can_player_move_to(game, game->player.pos_x, next_y))
		game->player.pos_y = next_y;
}

// on S , move backaards.
// newPos = pos - direction * speed
void	move_backward(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	next_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (can_player_move_to(game, next_x, game->player.pos_y))
		game->player.pos_x = next_x;
	if (can_player_move_to(game, game->player.pos_x, next_y))
		game->player.pos_y = next_y;
}

// on A, move left, (perpendicular to the facing direction) ?
void	move_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
	next_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	if (can_player_move_to(game, next_x, game->player.pos_y))
		game->player.pos_x = next_x;
	if (can_player_move_to(game, game->player.pos_x, next_y))
		game->player.pos_y = next_y;
}

// on D, move right (perpendicular to the facing direction)
void	move_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
	next_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	if (can_player_move_to(game, next_x, game->player.pos_y))
		game->player.pos_x = next_x;
	if (can_player_move_to(game, game->player.pos_x, next_y))
		game->player.pos_y = next_y;
}
