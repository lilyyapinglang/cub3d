/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:16 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 16:23:17 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	graceful_exit(t_game *game, int code)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img.img)
			mlx_destroy_image(game->mlx, game->tex[i].img.img);
		i++;
	}
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_all(game);
	exit(code);
}

int	handle_exit(t_game *game)
{
	graceful_exit(game, 0);
	return (0);
}
