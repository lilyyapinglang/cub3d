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
	int		fd;

	if (!path || path[0] == '\0')
		return (err_msg("", ERR_TEX_MISSING, 1));
	ext = ft_strrchr(path, '.');
	if (!ext || ft_strncmp(ext, ".xpm", 5) != 0)
		return (err_msg(path, ERR_XPM_FORMAT, 1));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_msg(path, ERR_TEX_NOT_FOUND, 1));
	close(fd);
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
	if (!game->has_floor || !game->has_ceiling)
		return (err_msg("", ERR_COLOR_MISSING, 1));
	return (0);
}
