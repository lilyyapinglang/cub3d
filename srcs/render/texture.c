#include "../../includes/cub3d.h"

void	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
	{
		perror("Error loading texture");
		free_all(game);
		exit(1);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
}

void	load_all_textures(t_game *game)
{
	printf("game->tex[0].path %s\n", game->tex[0].path);
	load_texture(game, &game->tex[0], game->tex[0].path);
	load_texture(game, &game->tex[1], game->tex[1].path);
	load_texture(game, &game->tex[2], game->tex[2].path);
	load_texture(game, &game->tex[3], game->tex[3].path);
}
