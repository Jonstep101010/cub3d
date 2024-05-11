#include "cube.h"
#include "input.h"
#include "utils.h"
#include "structs.h"
#include "defines.h"
#include <math.h>
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
		if (game->res->map_lines[dda->map_y].y_view[dda->map_x] == '1')
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

int	pixell(t_rgb color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
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
			color = rgb_to_hex(pixel[0], pixel[1], pixel[2]);
			mlx_put_pixel(game->image, col, t, color);
			draw->texture_y += draw->text_step;
		}
	}
}

void draw_ceiling_and_floor(t_cube *game, t_draw *draw, int col)
{
	int t = -1;
	while (++t < HEIGHT)
	{
		if (t < draw->start)
		{
			mlx_put_pixel(game->image, col, t, pixell(game->ceil_c));
		}
		else if (t > draw->end)
		{
			mlx_put_pixel(game->image, col, t, pixell(game->floor_c));
		}
	}
}

void	draw_texture(t_cube *game, int col, double perp_wall_dist)
{
	t_draw	draw;

	draw.height = (int)(HEIGHT / perp_wall_dist);

	draw.start =(HEIGHT / 2) - (draw.height / 2);
	draw.end = draw.height / 2 + (HEIGHT / 2);

	if((game->texture.side) == EAST || (game->texture.side) == WEST)
		draw.wall_x = game->player.y + perp_wall_dist * game->ray.dir_y;
	else
		draw.wall_x = game->player.x + perp_wall_dist * game->ray.dir_x;
	draw.wall_x -= floor(draw.wall_x);
		draw.texture_x = (int)(draw.wall_x * \
	(double)game->texture.texture[game->texture.side].width);
	draw.texture_y = 0; // Starts sampling from the top of the texture
	draw.text_step = (double)game->texture.texture[game->texture.side].height / (double)draw.height;
	if(draw.start < 0)
		draw.texture_y = fabs((double)draw.start) * draw.text_step;
	draw_ceiling_and_floor(game, &draw, col); 
	draw_wall_section(game, &draw, col); // Draw the wall section
}

void draw_map(t_cube *game)
{
	t_dda	dist;
	double	cam_x;
	int		i;

	i = -1;
	while(++i < WIDTH)
	{
		cam_x = 2 * i / (double)WIDTH - 1;
		game->ray.dir_x = game->player.dir_x + game->plane_x * cam_x;
		game->ray.dir_y = game->player.dir_y + game->plane_y * cam_x;
		if(game->ray.dir_x == 0)
			game->ray.delta_x = INFINITY;
		else
			game->ray.delta_x = fabs(1 /game->ray.dir_x);
		if(game->ray.dir_y == 0)
			game->ray.delta_x = INFINITY;
		else
			game->ray.delta_y = fabs(1 /game->ray.dir_y);
		dist = dda(game);
		if(game->texture.side == EAST || game->texture.side == WEST)
			draw_texture(game, i, dist.x - game->ray.delta_x);
		else
			draw_texture(game, i, dist.y - game->ray.delta_y);
	}
}
