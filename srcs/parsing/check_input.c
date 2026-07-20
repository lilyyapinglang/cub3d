/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:59 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 16:24:01 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_file(char *arg, bool cub)
{
	char	*ext;

	if (!arg)
		return (1);
	ext = ft_strrchr(arg, '.');
	if (!ext)
	{
		if (cub)
			return (err_msg(arg, ERR_CUB_FORMAT, 1));
		return (err_msg(arg, ERR_XPM_FORMAT, 1));
	}
	if (cub == true && ft_strncmp(ext, ".cub", 5) == 0)
		return (0);
	if (cub == false && ft_strncmp(ext, ".xpm", 5) == 0)
		return (0);
	if (cub)
		return (err_msg(arg, ERR_CUB_FORMAT, 1));
	return (err_msg(arg, ERR_XPM_FORMAT, 1));
}

size_t	max_line_width(t_game *game, int start)
{
	size_t	max;
	size_t	len;

	if (!game)
		return (0);
	max = 0;
	while (game->file.file_content[start])
	{
		len = ft_strlen(game->file.file_content[start]);
		if (len > 0 && game->file.file_content[start][len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		start++;
	}
	return (max);
}

int	validate_map(t_game *game)
{
	if (game->map.height == 0)
		return (err_msg("", ERR_MAP_MISSING, 1));
	if (check_map_size(game))
		return (1);
	if (check_chars(game))
		return (1);
	if (check_player(game))
		return (1);
	if (check_borders(game))
		return (1);
	return (0);
}

int	check_trailing_lines(t_game *game)
{
	int		i;
	char	*line;
	size_t	len;

	i = game->file.end_map + game->map.height;
	while (game->file.file_content[i])
	{
		line = game->file.file_content[i];
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len > 0)
			return (err_msg("", ERR_MAP_TRAILING, 1));
		i++;
	}
	return (0);
}
