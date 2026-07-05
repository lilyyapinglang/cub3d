#include "../../includes/cub3d.h"

static int	count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

static int	read_file(t_cub *cub)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(cub->file.fd);
	while (line)
	{
		cub->file.file_content[i] = line;
		i++;
		line = get_next_line(cub->file.fd);
	}
	cub->file.file_content[i] = NULL;
	return (0);
}

static void	dispatch_lines(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->file.file_content[i])
	{
		if (cub->file.file_content[i][0] == '\n'
			|| cub->file.file_content[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(cub->file.file_content[i], "NO ", 3)
			|| !ft_strncmp(cub->file.file_content[i], "SO ", 3)
			|| !ft_strncmp(cub->file.file_content[i], "WE ", 3)
			|| !ft_strncmp(cub->file.file_content[i], "EA ", 3))
			parse_textures(cub, cub->file.file_content[i]);
		else if (!ft_strncmp(cub->file.file_content[i], "F ", 2)
			|| !ft_strncmp(cub->file.file_content[i], "C ", 2))
			parse_colors(cub, cub->file.file_content[i]);
		else
			break ;
		i++;
	}
	cub->file.end_map = i;
}

int	parse_file(t_cub *cub, char **argv)
{
	if (is_valid_file(argv[1], true))
		return (1);
	cub->file.fd = open(argv[1], O_RDONLY);
	if (cub->file.fd < 0)
		return (err_msg(argv[1], ERR_FILE_OPEN, 1));
	cub->file.line_count = count_lines(cub->file.fd);
	close(cub->file.fd);
	cub->file.file_content = ft_calloc(cub->file.line_count + 1, sizeof(char *));
	if (!cub->file.file_content)
		return (err_msg("", ERR_MALLOC, 1));
	cub->file.fd = open(argv[1], O_RDONLY);
	if (cub->file.fd < 0)
		return (err_msg(argv[1], ERR_FILE_OPEN, 1));
	read_file(cub);
	close(cub->file.fd);
	dispatch_lines(cub);
	return (0);
}
