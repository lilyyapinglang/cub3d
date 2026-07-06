#include "../includes/cub3d.h"

static int	on_key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		graceful_exit(cub, 0);
	return (0);
}

static void	set_hooks(t_game *game)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, on_key_press, cub);
	mlx_hook(cub->win, ClientMessage, NoEventMask, handle_exit, cub);
}

char		*map[] = {"111111", "100001", "10N001", "100001", "111111", NULL};
game.map.grid = map;

game.player.x = 2.5;
game.player.y = 2.5;

game.floor = 0x00FF00;
game.ceiling = 0x87CEEB;

/*
MLX initialization
drawing pixels
raycasting
movement
collision
keyboard handling
*/
int	main(int argc, char **argv)
{
	t_game	cub;

	(void)argv;
	if (argc != 2)
		return (err_msg("", ERR_USAGE, 1));
	init_all(&cub);
	init_mlx(&cub);
	set_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
