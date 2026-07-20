/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:51 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 16:23:52 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	validate_texture_path(char *path)
{
	char	*ext;

	if (!path || path[0] == '\0')
		return (err_msg("", ERR_TEX_MISSING, 1));
	ext = ft_strrchr(path, '.');
	if (!ext || ft_strncmp(ext, ".xpm", 5) != 0)
		return (err_msg(path, ERR_FILE_FORMAT, 1));
	if (access(path, R_OK) != 0)
		return (err_msg(path, ERR_TEX_NOT_FOUND, 1));
	return (0);
}

static int	validate_texture_duplicates(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = i + 1;
		while (j < 4)
		{
			if (game->tex[i].path && game->tex[j].path
				&& ft_strlen(game->tex[i].path) == ft_strlen(game->tex[j].path)
				&& ft_strncmp(game->tex[i].path, game->tex[j].path,
					ft_strlen(game->tex[i].path)) == 0)
				return (err_msg(game->tex[i].path, ERR_TEX_DUPLICATE, 1));
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_config(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (validate_texture_path(game->tex[i].path))
			return (1);
		i++;
	}
	if (validate_texture_duplicates(game))
		return (1);
	if (!game->has_floor || !game->has_ceiling)
		return (err_msg("", ERR_COLOR_MISSING, 1));
	return (0);
}
