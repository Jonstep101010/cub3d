#include "cube.h"

void draw_map(t_cube *game)
{
	double	camera_x;
	double	wall_distance;
	int		x;

	while(x < SCREEN_WIDTH)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //normalize the screen x coord
		game->rays[x].originX = game->player.posX;
		game->rays[x].originY = game->player.posY;
		game->rays[x].dirX = game->player.dir_x + game->player.plane_x * cameraX;
		game->rays[x].dirY = game->player.dir_y + game->player.plane_y * cameraX;
  // Ray için DDA algoritmasını başlat
		initialize_ray(&game->player, &game->rays[x], cameraX);
		perform_dda(&game->rays[x], game->game_map.map);  // DDA algoritması uygulanır

		if (game->rays[x].side == 0)
			wall_distance = (game->rays[x].mapX - game->player.posX + (1 - game->rays[x].stepX) / 2) / game->rays[x].dirX;
		else
			wall_distance = (game->rays[x].mapY - game->player.posY + (1 - game->rays[x].stepY) / 2) / game->rays[x].dirY;

		draw_line(game, x, wall_distance);  // Texture'lı duvar çizimi

		x++;  // Sütun indeksini artır
	}
}