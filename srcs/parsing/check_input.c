#include "../../includes/cub3d.h"

int	is_valid_file(char *arg, bool cub)
{
	char	*ext;

	if (!arg)
		return (1);
	ext = ft_strrchr(arg, '.');
	if (!ext)
		return (err_msg(arg, ERR_FILE_FORMAT, 1));
	if (cub == true && ft_strncmp(ext, ".cub", 5) == 0)
		return (0);
	if (cub == false && ft_strncmp(ext, ".xpm", 5) == 0)
		return (0);
	return (err_msg(arg, ERR_FILE_FORMAT, 1));
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
		if (len > max)
			max = len;
		start++;
	}
	return (max);
}
