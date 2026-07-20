/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:46 by ylang             #+#    #+#             */
/*   Updated: 2026/07/20 16:23:47 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	read_file(t_game *game)
{
	int		i;
	char	*line;
	int		len;

	i = 0;
	line = get_next_line(game->file.fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->file.file_content[i] = line;
		i++;
		line = get_next_line(game->file.fd);
	}
	game->file.file_content[i] = NULL;
	return (0);
}

static int	line_treatement(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (parse_textures(game, line));
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (parse_colors(game, line));
	return (err_msg("", ERR_UNKNOWN_KEY, 1));
}

static int	dispatch_lines(t_game *game)
{
	int		i;

	i = 0;
	while (game->file.file_content[i])
	{
		if (!game->file.file_content[i][0])
		{
			i++;
			continue ;
		}
		if (!ft_strchr("NSWEFC", game->file.file_content[i][0]))
		{
			if (!ft_strchr("01NSEW ", game->file.file_content[i][0]))
				return (err_msg("", ERR_UNKNOWN_KEY, 1));
			break ;
		}
		if (line_treatement(game, game->file.file_content[i]))
			return (1);
		i++;
	}
	game->file.end_map = i;
	return (0);
}

int	parse_file(t_game *game, char **argv)
{
	if (is_valid_file(argv[1], true))
		return (1);
	game->file.fd = open(argv[1], O_RDONLY);
	if (game->file.fd < 0)
		return (err_msg(argv[1], ERR_FILE_OPEN, 1));
	game->file.line_count = count_lines(game->file.fd);
	close(game->file.fd);
	game->file.file_content = ft_calloc(game->file.line_count + 1,
			sizeof(char *));
	if (!game->file.file_content)
		return (err_msg("", ERR_MALLOC, 1));
	game->file.fd = open(argv[1], O_RDONLY);
	if (game->file.fd < 0)
		graceful_exit(game, 1);
	read_file(game);
	close(game->file.fd);
	get_next_line(-1);
	if (dispatch_lines(game) || validate_config(game)
		|| create_map(game) || check_trailing_lines(game)
		|| validate_map(game))
		graceful_exit(game, 1);
	return (0);
}
