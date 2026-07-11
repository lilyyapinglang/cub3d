#include "../../includes/cub3d.h"

void	draw_tile(t_game *game, int y, int x, bool filled)
{
	if (filled)
		draw_filled_rectangle(&game->img, x * TILE_SIZE, y * TILE_SIZE, (x + 1)
			* TILE_SIZE, (y + 1) * TILE_SIZE, 0xff0000);
	draw_rectangle(&game->img, x * TILE_SIZE, y * TILE_SIZE, (x + 1)
		* TILE_SIZE, (y + 1) * TILE_SIZE, 0xFFA500);
}

void	draw_map_tiles(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			// printf("y=%d x=%d\n", y, x);
			// printf("grid[%d] = %p\n", y, (void *)game->map.grid[y]);
			// printf("grid[i][j] is %c \n", game->map.grid[i][j]);
			if (game->map.grid[i][j] == '1')
				draw_tile(game, i, j, true);
			else
				draw_tile(game, i, j, false);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	// draw_rectangle(&game->img, game->player.pos_x * TILE_SIZE - 5,
	// 	game->player.pos_y * TILE_SIZE - 5, game->player.pos_x * TILE_SIZE + 5,
	// 	game->player.pos_y * TILE_SIZE + 5, 0xff0000);
	draw_filled_rectangle(&game->img, game->player.pos_x * TILE_SIZE - 2.5,
		game->player.pos_y * TILE_SIZE - 2.5, game->player.pos_x * TILE_SIZE
		+ 2.5, game->player.pos_y * TILE_SIZE + 2.5, 0xffff00);
}

void	draw_player_direction(t_game *game)
{
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;

	// dir ->
	start_x = game->player.pos_x;
	start_y = game->player.pos_y;
	// printf("player direction start point : %f %f", start_x, start_y);
	end_x = game->player.pos_x + game->player.dir_x;
	end_y = game->player.pos_y + game->player.dir_y;
	draw_line(&game->img, start_x * TILE_SIZE, start_y * TILE_SIZE, end_x
		* TILE_SIZE, end_y * TILE_SIZE, 0x00ff00);
	draw_filled_rectangle(&game->img, end_x * TILE_SIZE - 2.5, end_y * TILE_SIZE
		- 2.5, end_x * TILE_SIZE + 2.5, end_y * TILE_SIZE + 2.5, 0x00ff00);
}

void	draw_plane_direction(t_game *game)
{
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;

	// dir ->
	start_x = game->player.pos_x;
	start_y = game->player.pos_y;
	// printf("player direction start point : %f %f", start_x, start_y);
	end_x = game->player.pos_x + game->player.plane_x;
	end_y = game->player.pos_y + game->player.plane_y;
	draw_line(&game->img, start_x * TILE_SIZE, start_y * TILE_SIZE, end_x
		* TILE_SIZE, end_y * TILE_SIZE, 0xFF00FF);
	draw_filled_rectangle(&game->img, end_x * TILE_SIZE - 2.5, end_y * TILE_SIZE
		- 2.5, end_x * TILE_SIZE + 2.5, end_y * TILE_SIZE + 2.5, 0xFF00FF);
}
void	draw_minimap(t_game *game)
{
	// printf("height = %d\n", game->map.height);
	// printf("width = %d\n", game->map.width);
	// printf("grid = %p\n", (void *)game->map.grid);
	draw_map_tiles(game);
	draw_player(game);
	draw_player_direction(game);
	draw_plane_direction(game);
}