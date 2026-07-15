#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define BUFFER_SIZE 42
# define WIN_W 960
# define WIN_H 540
# define TEX_SIZE 64

# define ERR_USAGE "Required input: ./cub3D map.cub"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_FILE_OPEN "No such file or directory"
# define ERR_FILE_FORMAT ".cub and .xpm file extensions required"
# define ERR_MLX_INIT "Failed to initialize mlx"
# define ERR_MLX_WIN "Failed to create mlx window"
# define ERR_MLX_IMG "Failed to create mlx image"
# define ERR_TEX_MISSING "Texture files missing"
# define ERR_TEX_RGB "RGB value is invalid"
# define ERR_MAP_MISSING "Map data missing"
# define ERR_MAP_SIZE "Map must be at least 3x3"
# define ERR_MAP_CHARS "Invalid character in map"
# define ERR_MAP_PLAYER "Map must contain exactly one player"
# define ERR_MAP_OPEN "Map is not enclosed by walls"

typedef struct s_file
{
	int		fd;
	char	**file_content;
	int		line_count;
	int		end_map;
}	t_file;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture
{
	char	*path;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_texture	tex[4];
	int			floor;
	int			ceiling;
	t_file		file;
}	t_game;

void	init_all(t_game *game);
void	init_mlx(t_game *game);
void	graceful_exit(t_game *game, int code);
int		handle_exit(t_game *game);
int		free_all(t_game *game);
void	free_2d(void **arr);
int		err_msg(char *detail, char *msg, int code);
int		is_valid_file(char *arg, bool cub);
size_t	max_line_width(t_game *game, int start);
int		parse_file(t_game *game, char **argv);
int		parse_colors(t_game *game, char *line);
int		parse_textures(t_game *game, char *line);
int		create_map(t_game *game);
int		check_map_size(t_game *game);
int		check_borders(t_game *game);
int		check_chars(t_game *game);
int		check_player(t_game *game);
int		validate_map(t_game *game);
char	*get_next_line(int fd);

#endif
