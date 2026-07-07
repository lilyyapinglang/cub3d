#include "../../includes/cub3d.h"

void	init_all(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->floor = 0;
	game->ceiling = 0;
	game->file.fd = -1;
	game->file.file_content = NULL;
	game->file.line_count = 0;
	game->file.end_map = 0;
	i = 0;
	while (i < 4)
	{
		game->tex[i].path = NULL;
		i++;
	}
}
