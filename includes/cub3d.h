#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WIN_W 960
# define WIN_H 540
# define TEX_SIZE 64

# define ERR_USAGE "Required input: ./cub3D map.cub"
# define ERR_MLX_INIT "Failed to initialize mlx"
# define ERR_MLX_WIN "Failed to create mlx window"
# define ERR_MLX_IMG "Failed to create mlx image"

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	char	**map;
}	t_cub;

void	init_all(t_cub *cub);
void	init_mlx(t_cub *cub);
void	graceful_exit(t_cub *cub, int code);
int		handle_exit(t_cub *cub);
int		free_all(t_cub *cub);
void	free_2d(void **arr);
int		err_msg(char *detail, char *msg, int code);

#endif
