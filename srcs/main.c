#include "../includes/cub3d.h"

static int	on_key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		graceful_exit(game, 0);
	return (0);
}

static void	set_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, on_key_press, game);
	mlx_hook(game->win, ClientMessage, NoEventMask, handle_exit, game);
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
	set_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
