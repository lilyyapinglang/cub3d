#include "../../includes/cub3d.h"

void	graceful_exit(t_game *game, int code)
{
	int	i;

	fprintf(stderr, "pointer = %p, ", game->img.img);
	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img.img)
			mlx_destroy_image(game->mlx, game->tex[i].img.img);
		i++;
	}
	if (game->img.img)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		// free(game->img.img);
	}
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
	// write(1,
	// "hellllllllllllllllllllllllllllllllllllllllpppppppppppppppppppppppppppppp",
	// 72);
	// fprintf(stderr, "pointer = %p, ", game->img.img);
	graceful_exit(game, 0);
	return (0);
}
