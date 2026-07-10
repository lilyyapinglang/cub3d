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
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			printf("y=%d x=%d\n", y, x);
			printf("grid[%d] = %p\n", y, (void *)game->map.grid[y]);
			if (game->map.grid[y][x] == '1')
				draw_tile(game, x, y, true);
			else
				draw_tile(game, x, y, false);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	draw_rectangle(&game->img, game->player.pos_x * TILE_SIZE,
		game->player.pos_y * TILE_SIZE, game->player.pos_x * TILE_SIZE + 10,
		game->player.pos_y * TILE_SIZE + 10, 0xff0000);
}

void	draw_player_direction(t_game *game)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	// dir ->
	start_x = game->player.pos_x;
	start_y = game->player.pos_y;
	end_x = game->player.pos_x + game->player.dir_x;
	end_y = game->player.pos_y + game->player.dir_y;
	draw_line(&game->img, start_x * TILE_SIZE, start_y * TILE_SIZE, end_x
		* TILE_SIZE, end_y * TILE_SIZE, 0x008000);
}
void	draw_minimap(t_game *game)
{
	printf("height = %d\n", game->map.height);
	printf("width = %d\n", game->map.width);
	printf("grid = %p\n", (void *)game->map.grid);
	draw_map_tiles(game);
	draw_player(game);
	draw_player_direction(game);
}
