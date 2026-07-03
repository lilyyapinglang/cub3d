#include "../includes/cub3d.h"

static int	on_key_press(int key, t_cub *cub)
{
	if (key == XK_Escape)
		graceful_exit(cub, 0);
	return (0);
}

static void	set_hooks(t_cub *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, on_key_press, cub);
	mlx_hook(cub->win, ClientMessage, NoEventMask, handle_exit, cub);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	(void)argv;
	if (argc != 2)
		return (err_msg("", ERR_USAGE, 1));
	init_all(&cub);
	init_mlx(&cub);
	set_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
