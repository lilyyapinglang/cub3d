#include "../../includes/cub3d.h"

static int	count_map_lines(t_game *game)
{
	int		count;
	int		start;
	char	*line;
	size_t	len;

	start = game->file.end_map;
	count = 0;
	while (game->file.file_content[start + count])
	{
		line = game->file.file_content[start + count];
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len == 0)
			break ;
		count++;
	}
	return (count);
}

static char	*pad_line(char *line, size_t width)
{
	size_t	len;
	char	*padded;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	len = ft_strlen(line);
	padded = ft_calloc(width + 1, 1);
	if (!padded)
		return (NULL);
	ft_memset(padded, ' ', width);
	ft_memcpy(padded, line, len);
	return (padded);
}

int	create_map(t_game *game)
{
	int		i;
	int		start;
	size_t	width;

	start = game->file.end_map;
	game->map.height = count_map_lines(game);
	width = max_line_width(game, start);
	game->map.width = width;
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (err_msg("", ERR_MALLOC, 1));
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = pad_line(
				game->file.file_content[start + i], width);
		if (!game->map.grid[i])
			return (err_msg("", ERR_MALLOC, 1));
		i++;
	}
	game->map.grid[i] = NULL;
	return (0);
}
