#include "../../includes/cub3d.h"

void	free_2d(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	free_all(t_game *game)
{
	int	i;

	if (game->map.grid)
		free_2d((void **)game->map.grid);
	if (game->file.file_content)
		free_2d((void **)game->file.file_content);
	i = 0;
	while (i < 4)
	{
		if (game->tex[i].path)
			free(game->tex[i].path);
		i++;
	}
	return (0);
}
