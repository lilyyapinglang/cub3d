/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:17:50 by ylang             #+#    #+#             */
/*   Updated: 2026/07/18 18:58:57 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, on_key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, on_key_relase, game);
	mlx_hook(game->win, ClientMessage, NoEventMask, handle_exit, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	load_data(t_game *game)
{
	load_player(game);
	game->keys.key_a = false;
	game->keys.key_d = false;
	game->keys.key_s = false;
	game->keys.key_w = false;
	game->keys.key_left = false;
	game->keys.key_right = false;
	init_load_texture_from_file(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (err_msg("", ERR_USAGE, 1));
	init_all(&game);
	if (parse_file(&game, argv))
		return (1);
	init_mlx(&game);
	load_data(&game);
	set_hooks(&game);
	mlx_loop(game.mlx);
	graceful_exit(&game, 0);
}
