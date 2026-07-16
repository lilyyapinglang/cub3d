#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42
# define WIN_W 1280
# define WIN_H 720
# define TILE_SIZE 16

# define MINIMAP_START_X 20
# define MINIMAP_START_Y 20
# define TEX_SIZE 64

# define NORTH_TEX 0
# define SOUTH_TEX 1
# define WEST_TEX 2
# define EAST_TEX 3

# define MOVE_SPEED 0.01
// radians, not degrees,  convert to degrees 0.05*180/PI =2.86°
# define ROTATION_SPEED 0.01
# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
# endif

# define ERR_USAGE "Required input: ./cub3D map.cub"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_FILE_OPEN "No such file or directory"
# define ERR_FILE_FORMAT ".cub and .xpm file extensions required"
# define ERR_MLX_INIT "Failed to initialize mlx"
# define ERR_MLX_WIN "Failed to create mlx window"
# define ERR_MLX_OUT_SCREEN "Out of screen size"
# define ERR_MLX_IMG "Failed to create mlx image"
# define ERR_TEX_MISSING "Texture files missing"
# define ERR_TEX_RGB "RGB value is invalid"
# define ERR_MAP_MISSING "Map data missing"

typedef struct s_file
{
	int			fd;
	char		**file_content;
	int			line_count;
	int			end_map;
}				t_file;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_texture
{
	int			width;
	int			height;
	t_img		img;
	char		*path;
}				t_texture;

typedef struct s_ray
{
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		deltaDistX;
	double		deltaDistY;
	int			hit;
	int			side;
	int			stepX;
	int			stepY;
	double		sideDistX;
	double		sideDistY;
	double		perpWallDist;
	double		lineHeight;
	double		drawStart;
	double		drawEnd;

}				t_ray;

typedef struct s_key
{
	bool		key_w;
	bool		key_a;
	bool		key_s;
	bool		key_d;
	bool		key_left;
	bool		key_right;
}				t_key;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_texture	tex[4];
	int			floor;
	int			ceiling;
	t_img		img;
	t_file		file;
	t_key		keys;
	t_ray		ray;
}				t_game;

void			init_all(t_game *game);
void			init_mlx(t_game *game);
void			graceful_exit(t_game *game, int code);
int				handle_exit(t_game *game);
int				free_all(t_game *game);
void			free_2d(void **arr);
int				err_msg(char *detail, char *msg, int code);
int				is_valid_file(char *arg, bool cub);
size_t			max_line_width(t_game *game, int start);
int				parse_file(t_game *game, char **argv);
int				parse_colors(t_game *game, char *line);
int				parse_textures(t_game *game, char *line);
char			*get_next_line(int fd);

// rendering
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_floor(t_game *game);
void			draw_ceiling(t_game *game);
void			draw_player(t_game *game);
int				draw_line(t_img *img, int begin_x, int begin_y, int end_x,
					int end_y, int color);
void			draw_rectangle(t_img *img, int begin_x, int begin_y, int end_x,
					int end_y, int color);
void			draw_filled_rectangle(t_img *img, int point1_x, int point1_y,
					int point2_x, int point2_y, int color);
// draw minimap
void			draw_minimap(t_game *game);
// listening events
int				on_key_press(int key, t_game *game);
int				on_key_relase(int key, t_game *game);

// movement functions
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

// check collision
bool			can_player_move_to(t_game *game, double next_x, double next_y);

// draw wall aka raycasting
void			raycasting(t_game *game);

// hooks & loop
int				game_loop(t_game *game);

// textures
void			load_all_textures(t_game *game);

// raycasting
void			init_ray_params(int x, t_game *game);
void			cal_step_n_sidedist(t_game *game);
void			perform_dda(t_game *game);
#endif
