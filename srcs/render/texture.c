/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:15:20 by ylang             #+#    #+#             */
/*   Updated: 2026/07/18 16:02:07 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img.img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img.img)
	{
		perror("Error loading texture");
		free_all(game);
		exit(1);
	}
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
			&tex->img.line_length, &tex->img.endian);
}

void	load_all_textures(t_game *game)
{
	load_texture(game, &game->tex[NORTH_TEX], game->tex[NORTH_TEX].path);
	load_texture(game, &game->tex[SOUTH_TEX], game->tex[SOUTH_TEX].path);
	load_texture(game, &game->tex[WEST_TEX], game->tex[WEST_TEX].path);
	load_texture(game, &game->tex[EAST_TEX], game->tex[EAST_TEX].path);
}
