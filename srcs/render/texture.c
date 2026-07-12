#include "../../includes/cub3d.h"

void	load_texture(t_game *game, t_texture *texture)
{
	texture->img.img == mlx_xpm_file_to_image(game->mlx, texture->path,
			&texture->width, &texture->height);
	if (texture->img.img)
	{
		perror("Error loading texture");
		// freeall(mapa);
		// exit(1);
	}
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
}

void	load_all_textures(t_game *game)
{
	load_texture(game, &game->tex[0]);
	load_texture(game, &game->tex[1]);
	load_texture(game, &game->tex[2]);
	load_texture(game, &game->tex[3]);
}