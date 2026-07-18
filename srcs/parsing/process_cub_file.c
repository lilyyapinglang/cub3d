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
	size_t	len;
	char	*path;

	i = get_tex_index(line);
	if (i == -1)
		return (1);
	path = ft_strdup(line + 3);
	if (!path)
		return (err_msg("", ERR_MALLOC, 1));
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	if (game->tex[i].path)
		free(game->tex[i].path);
	game->tex[i].path = path;
	return (0);
}

static int	validate_rgb(char **split)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!split[i])
			return (1);
		if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255)
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
	int		r;
	int		g;
	int		b;

	split = ft_split(line + 2, ',');
	if (!split)
		return (err_msg("", ERR_MALLOC, 1));
	if (validate_rgb(split))
	{
		free_2d((void **)split);
		return (err_msg("", ERR_TEX_RGB, 1));
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_2d((void **)split);
	set_color(game, line[0], (r << 16) | (g << 8) | b);
	return (0);
}
