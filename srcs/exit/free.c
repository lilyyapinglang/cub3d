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
	if (cub->map)
		free_2d((void **)cub->map);
	return (0);
}
