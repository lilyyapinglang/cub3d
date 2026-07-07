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

static char	*clean_path(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	parse_textures(t_game *game, char *line)
{
	int		i;
	char	*path;

	i = get_tex_index(line);
	if (i == -1)
		return (1);
	path = clean_path(ft_strdup(line + 3));
	if (!path)
		return (err_msg("", ERR_MALLOC, 1));
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
	if (line[0] == 'F')
		game->floor = (r << 16) | (g << 8) | b;
	else
		game->ceiling = (r << 16) | (g << 8) | b;
	return (0);
}
