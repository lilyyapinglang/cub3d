#include "../../includes/cub3d.h"

/*
 every frame

 clear image
 cast rays
 draw walls with put_pixels()
 draw floor/ceiling
 mlx_put_image_to_window()

*/

/* for every screen column
	x from 0 - width
	cast ray -> hit wall - > calculate distance -> draw vertica lines
 raycast every column
		↓
	draw wall slice

*/

void	raycsting(t_game *game, int x)
{
	(void)game;
	(void)x;
}

void	render(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		raycsting(game, x);
	}
}

void	update_game(t_game *game)
{
	// update player
	(void)game;
}

void	clear_image(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
//根据当前输入，改变游戏状态。 把输入(Input)转换成游戏行为(Action)
//具体，6个按键 改变 pos dir 和 plane
void	handle_input(t_game *game)
{
	if (game->keys.key_w)
		move_forward(game);
	if (game->keys.key_s)
		move_backward(game);
	if (game->keys.key_a)
		move_left(game);
	if (game->keys.key_d)
		move_right(game);
	if (game->keys.key_left)
		rotate_left(game);
	if (game->keys.key_right)
		rotate_right(game);
}
void	render_game(t_game *game)
{
	// put_pixel(&game->img, WIN_W / 2, WIN_H / 2, 0xFF0000);
	// draw_line(&game->img, WIN_W / 2, 0, WIN_W / 2, WIN_H, 0xFF0000);
	// draw_rectangle(&game->img, WIN_W / 2 - 1, WIN_H / 2 - 1, WIN_W / 2 + 1,
	// 	WIN_H / 2 + 1, 0xFFA500);
	clear_image(&game->img, 0);
	draw_floor(game);
	draw_ceiling(game);
	// draw_filled_rectangle(&game->img, WIN_W / 2 - 100, WIN_H / 2 - 100, WIN_W
	// 	/ 2 + 100, WIN_H / 2 + 100, 0xFFA500);
	// will add raycasting later, render_world(game); draw wall；
	draw_minimap(game);
	// draw ui , later， FPS: 60 etc 武器 血量 子弹数量
}

/*
Input
	↓
Update
	↓
Render
*/
int	game_loop(t_game *game)
{
	handle_input(game);
	update_game(game);
	render_game(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}