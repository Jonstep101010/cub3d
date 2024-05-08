#include "cube.h"
#include <stdint.h>

void wall_collision(t_cube *game, t_dda *dda)
{
	while (true)
	{
		if (dda->x < dda->y)
		{
			dda->x += game->ray.delta_x;
			dda->map_x += dda->step_x;
			if (game->ray.dir_x > 0)
				game->texture.side = EAST;
			else
				game->texture.side = WEST;
		}
		else
		{
			dda->y += game->ray.delta_y;
			dda->map_y += dda->step_y;
			if (game->ray.dir_y > 0)
				game->texture.side = SOUTH;
			else
				game->texture.side = NORTH;
		}
		if (game->game_map.map[dda->map_y][dda->map_x] == '1')
			break ;
	}
}

t_dda	dda(t_cube	*game)
{
	t_dda	dda;

	dda.map_x = (int)(game->player.x);
	dda.map_y = (int)(game->player.y);
	dda.step_x = 1;
	dda.step_y = 1;
	if (game->ray.dir_x < 0)
	{
		dda.step_x = -1;
		dda.x = (game->player.x - dda.map_x) *  game->ray.delta_x;
	}
	else
		dda.x = (dda.map_x + 1.0 - game->player.dir_x) * game->ray.delta_x;
	if (game->ray.dir_y < 0)
	{
		dda.step_x = -1;
		dda.y = (game->player.y - dda.map_y) *  game->ray.delta_y;
	}
	else
		dda.y = (dda.map_y + 1.0 - game->player.dir_y) * game->ray.delta_y;
	wall_collision(game, &dda);
	return(dda);

}

int	pixell(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_wall_section(t_cube *game, t_draw *draw, int col)
{
	unsigned int color;
	int t = draw->start - 1; // Start from the beginning of the wall section
	uint8_t *pixel;
	int num;

	// Loop over each pixel in the wall section vertically
	while (++t <= draw->end)
	{
		if (draw->texture_y < game->texture.texture[game->texture.side].height)
		{
			num = game->texture.texture[game->texture.side].width * 4 * (int)draw->texture_y + (int)draw->texture_x * 4;
			pixel = &game->texture.texture[game->texture.side].pixels[num];
			color = pixell(pixel[0], pixel[1], pixel[2], pixel[3]);
			mlx_put_pixel(game->image, col, t, color);
			draw->texture_y += draw->text_step;
		}
	}
}

void draw_ceiling_and_floor(t_cube *game, t_draw *draw, int col)
{
	int t = -1;
	while (++t < SCREEN_HEIGHT)
	{
		if (t < draw->start)
		{
			mlx_put_pixel(game->image, col, t, pixell(game->ceil_c.r, game->ceil_c.g, game->ceil_c.b, 255));
		}
		else if (t > draw->end)
		{
			mlx_put_pixel(game->image, col, t, pixell(game->floor_c.r, game->floor_c.g, game->floor_c.b, 255));
		}
	}
}

void	draw_texture(t_cube *game, int col, double perp_wall_dist)
{
	t_draw	draw;

	draw.height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		// Calculate the starting and ending y-coordinates for the line on the screen.
	// This centers the line vertically based on its calculated height.
	draw.start =(SCREEN_HEIGHT / 2) - (draw.height / 2);     // Çizimin başlayacağı y noktası
	draw.end = draw.height / 2 + (SCREEN_HEIGHT / 2);

	if((game->texture.side) == EAST || (game->texture.side) == WEST)
		draw.wall_x = game->player.y + perp_wall_dist * game->ray.dir_y;
	else
		draw.wall_x = game->player.x + perp_wall_dist * game->ray.dir_x;

	 // Use only the fractional part of the wall x-coordinate by subtracting its floor value.
	// This is essential for correct texture wrapping and alignment on the wall.
	draw.wall_x -= floor(draw.wall_x);

// Calculate the exact horizontal position within the texture from which to sample pixels
		draw.texture_x = (int)(draw.wall_x * \
	(double)game->texture.texture[game->texture.side].width);

	// Initialize the texture sampling position along the y-axis of the texture
	draw.texture_y = 0; // Starts sampling from the top of the texture

	// Calculate the rate at which to move down the texture's y-axis per screen pixel drawn
	draw.text_step = (double)game->texture.texture[game->texture.side].height / (double)draw.height;  // Adjust texture sampling rate based on line height

	// Adjust the texture sampling start position if the top of the wall slice is off-screen
	if(draw.start < 0)  // If the starting point is above the screen
		draw.texture_y = fabs((double)draw.start) * draw.text_step;  //adjust text_y to skip the unseen part of the texture

	draw_ceiling_and_floor(game, &draw, col); // Draw ceiling and floor
	draw_wall_section(game, &draw, col); // Draw the wall section
}

void draw_map(t_cube *game)
{
	t_dda	dist;
	double	cam_x;
	int		i;

	i = -1;
	while(++i < SCREEN_WIDTH)
	{
		cam_x = 2 * i / (double)SCREEN_WIDTH - 1;
		game->ray.dir_x = game->player.dir_x + game->plane_x * cam_x;
		game->ray.dir_y = game->player.dir_y + game->plane_y * cam_x;
		if(game->ray.dir_x == 0)
			game->ray.delta_x = 1e30;
		else
		 game->ray.delta_x = fabs(1 /game->ray.dir_x);
		if(game->ray.dir_y == 0)
			game->ray.delta_x = 1e30;
		else
		 game->ray.delta_y = fabs(1 /game->ray.dir_y);
		dist = dda(game);
		if(game->texture.side == EAST || game->texture.side == WEST)
			draw_texture(game, i, dist.x - game->ray.delta_x);
		else
			draw_texture(game, i, dist.y - game->ray.delta_y);
	}
}
