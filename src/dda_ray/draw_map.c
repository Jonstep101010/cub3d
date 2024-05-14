#include "cube.h"
#include "utils.h"
#include "defines.h"
#include <math.h>
#include <stdio.h>
#include "input.h"

t_dda	dda(t_cube_data	*cubed);

void debug_raycast(t_cube_data *cubed, t_dda *dda)
{
	printf("Ray Pos: (%f, %f), Ray Dir: (%f, %f)\n", cubed->player.x, cubed->player.y, cubed->ray.dir_x, cubed->ray.dir_y);
	printf("Step: (X: %d, Y: %d), Delta: (X: %f, Y: %f)\n", dda->step_x, dda->step_y, cubed->ray.delta_x, cubed->ray.delta_y);
	printf("Map Position: (X: %d, Y: %d), Side: %d\n", dda->map_x, dda->map_y, cubed->texture_side);

	if (cubed->res->map_lines[dda->map_y].y_view[dda->map_x] == '1')
		printf("Wall hit at: (X: %d, Y: %d)\n", dda->map_x, dda->map_y);
	else
		printf("No wall hit yet.\n");
}

static void draw_wall_section(t_cube_data *cubed, t_draw *draw, int col)
{
	int t = draw->start - 1; // Start from the beginning of the wall section
	int num;

	// Loop over each pixel in the wall section vertically
	while (++t <= draw->end && t < HEIGHT)
	{
		if (draw->texture_y < cubed->res->tex[cubed->texture_side]->height)
		{
			num = cubed->res->tex[cubed->texture_side]->width * 4 * (int)draw->texture_y + (int)draw->texture_x * 4;
			mlx_put_pixel(cubed->image, col, t, rgb_arr_hex(
				&cubed->res->tex[cubed->texture_side]->pixels[num]));
			draw->texture_y += draw->text_step;
		}
	}
}

static void draw_ceiling_and_floor(t_cube_data *cubed, t_draw *draw, int col)
{
	int t = -1;
	while (++t < HEIGHT)
	{
		if (t < draw->start)
		{
			mlx_put_pixel(cubed->image, col, t, cubed->res->ceiling);
		}
		else if (t > draw->end)
		{
			mlx_put_pixel(cubed->image, col, t, cubed->res->floor);
		}
	}
}

static void	draw_column(t_cube_data *cubed, int col, double perp_wall_dist)
{
	t_draw	draw;

	draw.height = (int)(HEIGHT / perp_wall_dist);
	draw.start = (HEIGHT / 2) - (draw.height / 2);
	draw.end = (draw.height / 2) + (HEIGHT / 2);

	if(cubed->texture_side == E || cubed->texture_side == W)
		draw.wall_x = cubed->player.y + perp_wall_dist * cubed->ray.dir_y;
	else
		draw.wall_x = cubed->player.x + perp_wall_dist * cubed->ray.dir_x;
	draw.wall_x -= floor(draw.wall_x);
		draw.texture_x = (int)(draw.wall_x * \
	(double)cubed->res->tex[cubed->texture_side]->width);
	draw.texture_y = 0; // Starts sampling from the top of the texture
	draw.text_step = (double)cubed->res->tex[cubed->texture_side]->height / (double)draw.height;
	if (draw.start < 0)
	{
		draw.start = 0;
		draw.texture_y = fabs((double)draw.start) * draw.text_step;
	}
	draw_ceiling_and_floor(cubed, &draw, col);
	draw_wall_section(cubed, &draw, col); // Draw the wall section
}

void draw_map(t_cube_data *cubed)
{
	t_dda	dist;
	double	cam_x;
	int		i;

	i = -1;
	while(++i < WIDTH)
	{
		cam_x = 2 * i / (double)WIDTH - 1;
		cubed->ray.dir_x = cubed->player.dir_x + cubed->player.plane_x * cam_x;
		cubed->ray.dir_y = cubed->player.dir_y + cubed->player.plane_y * cam_x;
		if (cubed->ray.dir_x == 0)
			cubed->ray.delta_x = INFINITY;
		else
			cubed->ray.delta_x = fabs(1 /cubed->ray.dir_x);
		if (cubed->ray.dir_y == 0)
			cubed->ray.delta_y = INFINITY;
		else
			cubed->ray.delta_y = fabs(1 /cubed->ray.dir_y);
		dist = dda(cubed);
		// debug_raycast(cubed, &dda);  // Debugging line
		if(cubed->texture_side == E || cubed->texture_side == W)
			draw_column(cubed, i, dist.x - cubed->ray.delta_x);
		else
			draw_column(cubed, i, dist.y - cubed->ray.delta_y);
	}
}
