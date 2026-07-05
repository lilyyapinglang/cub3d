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

typedef struct s_file
{
	int		fd;
	char	*path;
	char	**file_content;
	int		line_count;
	int		end_map;
	int		map_w;
	int		map_h;
}	t_file;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	char	**map;
	t_file		file;
}	t_cub;

void	init_all(t_cub *cub);
void	init_mlx(t_cub *cub);
void	graceful_exit(t_cub *cub, int code);
int		handle_exit(t_cub *cub);
int		free_all(t_cub *cub);
void	free_2d(void **arr);
int		err_msg(char *detail, char *msg, int code);
int		is_valid_file(char *arg, bool cub);
size_t	max_line_width(t_cub *cub, int start);
int		parse_file(t_cub *cub, char **argv);
int		parse_colors(t_cub *cub, char *line);
int     parse_textures(t_cub *cub, char *line);
char	*get_next_line(int fd);

#endif
