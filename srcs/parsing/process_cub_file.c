#include "../../includes/cub3d.h"

static int	get_tex_index(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (0);
	if (!ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "EA ", 3))
		return (2);
	if (!ft_strncmp(line, "WE ", 3))
		return (3);
	return (-1);
}

int	parse_textures(t_game *game, char *line)
{
	int		i;
	char	*path;
	char	*p;

	i = get_tex_index(line);
	if (i == -1)
		return (1);
	p = line + 3;
	while (*p == ' ')
		p++;
	path = ft_strdup(p);
	if (!path)
		return (err_msg("", ERR_MALLOC, 1));
	if (game->tex[i].path)
	{
		free(path);
		return (err_msg(game->tex[i].path, ERR_TEX_DUPLICATE, 1));
	}
	game->tex[i].path = path;
	return (0);
}

static int	validate_rgb(char **split)
{
	int		i;
	int		j;

	if (!split[0] || !split[1] || !split[2] || split[3])
		return (1);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] < '0' || split[i][j] > '9')
				return (1);
			j++;
		}
		if (ft_atoi(split[i]) > 255)
			return (1);
		i++;
	}
	return (0);
}

static void	set_color(t_game *game, char id, int color)
{
	if (id == 'F')
	{
		game->floor = color;
		game->has_floor = true;
	}
	else
	{
		game->ceiling = color;
		game->has_ceiling = true;
	}
}

int	parse_colors(t_game *game, char *line)
{
	char	**split;
	char	*p;
	int		color;

	if ((line[0] == 'F' && game->has_floor)
		|| (line[0] == 'C' && game->has_ceiling))
		return (err_msg("", ERR_COLOR_DUPLICATE, 1));
	p = line + 2;
	while (*p == ' ')
		p++;
	split = ft_split(p, ',');
	if (!split)
		return (err_msg("", ERR_MALLOC, 1));
	if (validate_rgb(split))
	{
		free_2d((void **)split);
		return (err_msg("", ERR_TEX_RGB, 1));
	}
	color = (ft_atoi(split[0]) << 16) | (ft_atoi(split[1]) << 8)
		| ft_atoi(split[2]);
	free_2d((void **)split);
	set_color(game, line[0], color);
	return (0);
}
