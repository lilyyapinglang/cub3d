/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:50 by ylang             #+#    #+#             */
/*   Updated: 2026/07/16 19:29:47 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// hit the wall -> stop  , not conituning
// if not hit the all, update positions.

bool	can_player_move_to(t_game *game, double next_x, double next_y)
{
	printf("next step player at %f %f \n", next_x, next_y);
	printf("int pos_x = %d int pos_y = %d\n", (int)next_x, (int)next_y);
	printf("grid is %c\n", game->map.grid[(int)next_y][(int)next_x]);
	if (game->map.grid[(int)next_y][(int)next_x] == '1'
		|| next_y >= (double)(game->map.height - 1) || next_y <= 0
		|| next_x >= (double)(game->map.width - 1) - MOVE_SPEED
		|| next_x <= MOVE_SPEED)
		return (false);
	return (true);
}
