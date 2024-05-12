// #include "cube.h"
// #include "input.h"
// #include "utils.h"
// #include "structs.h"
// #include "defines.h"
// #include <math.h>
// #include <stdint.h>

// void debug_raycast(t_game *game, t_coord *dda)
// {
//     printf("Ray Pos: (%f, %f), Ray Dir: (%f, %f)\n", game->player.x, game->player.y, game->ray.x, game->ray.y);
//     printf("Step: (X: %d, Y: %d), Delta: (X: %f, Y: %f)\n", dda->step_x, dda->step_y, game->ray.delta_x, game->ray.delta_y);
//     printf("Map Position: (X: %d, Y: %d), Side: %d\n", dda->map_x, dda->map_y, game->wall.side);

//     if (game->map.map[dda->map_y][dda->map_x] == '1')
//         printf("Wall hit at: (X: %d, Y: %d)\n", dda->map_x, dda->map_y);
//     else
//         printf("No wall hit yet.\n");
// }

// void draw_map(t_cube *cubed)
// {
// 	t_dda	dist;
// 	double	cam_x;
// 	int		i;

// 	i = -1;
// 	while(++i < WIDTH)
// 	{
// 		cam_x = 2 * i / (double)WIDTH - 1;
// 		cubed->ray.dir_x = cubed->player.dir_x + cubed->plane_x * cam_x;
// 		cubed->ray.dir_y = cubed->player.dir_y + cubed->plane_y * cam_x;
// 		if(cubed->ray.dir_x == 0)
// 			cubed->ray.delta_x = INFINITY;
// 		else
// 			cubed->ray.delta_x = fabs(1 /cubed->ray.dir_x);
// 		if(cubed->ray.dir_y == 0)
// 			cubed->ray.delta_x = INFINITY;
// 		else
// 			cubed->ray.delta_y = fabs(1 /cubed->ray.dir_y);
// 		dist = dda(cubed);
// 		if(cubed->texture.side == EAST || cubed->texture.side == WEST)
// 			draw_texture(cubed, i, dist.x - cubed->ray.delta_x);
// 		else
// 			draw_texture(cubed, i, dist.y - cubed->ray.delta_y);
// 	}
// }

// t_dda	dda(t_cube	*cubed)
// {
// 	t_dda	dda;

// 	dda.map_x = (int)(cubed->player.x);
// 	dda.map_y = (int)(cubed->player.y);
// 	dda.step_x = 1;
// 	dda.step_y = 1;
// 	if (cubed->ray.dir_x < 0)
// 	{
// 		dda.step_x = -1;
// 		dda.x = (cubed->player.x - dda.map_x) *  cubed->ray.delta_x;
// 	}
// 	else
// 		dda.x = (dda.map_x + 1.0 - cubed->player.dir_x) * cubed->ray.delta_x;
// 	if (cubed->ray.dir_y < 0)
// 	{
// 		dda.step_x = -1;
// 		dda.y = (cubed->player.y - dda.map_y) *  cubed->ray.delta_y;
// 	}
// 	else
// 		dda.y = (dda.map_y + 1.0 - cubed->player.dir_y) * cubed->ray.delta_y;
// 	wall_collision(cubed, &dda);
// 	debug_raycast(game, dda);  // Debugging line
// 	return(dda);

// }

// void wall_collision(t_cube_data *cubed, t_dda *dda)
// {
// 	while (true)
// 	{
// 		if (dda->x < dda->y)
// 		{
// 			dda->x += cubed->ray.delta_x;
// 			dda->map_x += dda->step_x;
// 			if (cubed->ray.dir_x > 0)
// 				cubed->texture.side = EAST;
// 			else
// 				cubed->texture.side = WEST;
// 		}
// 		else
// 		{
// 			dda->y += cubed->ray.delta_y;
// 			dda->map_y += dda->step_y;
// 			if (cubed->ray.dir_y > 0)
// 				cubed->texture.side = SOUTH;
// 			else
// 				cubed->texture.side = NORTH;
// 		}
// 		if (cubed->res->map_lines[dda->map_y].y_view[dda->map_x] == '1')
// 			break ;
// 	}
// }



// int	pixell(t_rgb color)
// {
// 	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
// }

// void draw_wall_section(t_cube *cubed, t_draw *draw, int col)
// {
// 	unsigned int color;
// 	int t = draw->start - 1; // Start from the beginning of the wall section
// 	uint8_t *pixel;
// 	int num;

// 	// Loop over each pixel in the wall section vertically
// 	while (++t <= draw->end)
// 	{
// 		if (draw->texture_y < cubed->texture.texture[cubed->texture.side].height)
// 		{
// 			num = cubed->texture.texture[cubed->texture.side].width * 4 * (int)draw->texture_y + (int)draw->texture_x * 4;
// 			pixel = &cubed->texture.texture[cubed->texture.side].pixels[num];
// 			color = rgb_to_hex(pixel[0], pixel[1], pixel[2]);
// 			mlx_put_pixel(cubed->image, col, t, color);
// 			draw->texture_y += draw->text_step;
// 		}
// 	}
// }

// void draw_ceiling_and_floor(t_cube *cubed, t_draw *draw, int col)
// {
// 	int t = -1;
// 	while (++t < HEIGHT)
// 	{
// 		if (t < draw->start)
// 		{
// 			mlx_put_pixel(cubed->image, col, t, pixell(cubed->ceil_c));
// 		}
// 		else if (t > draw->end)
// 		{
// 			mlx_put_pixel(cubed->image, col, t, pixell(cubed->floor_c));
// 		}
// 	}
// }

// void	draw_texture(t_cube *cubed, int col, double perp_wall_dist)
// {
// 	t_draw	draw;

// 	draw.height = (int)(HEIGHT / perp_wall_dist);

// 	draw.start =(HEIGHT / 2) - (draw.height / 2);
// 	draw.end = draw.height / 2 + (HEIGHT / 2);

// 	if((cubed->texture.side) == EAST || (cubed->texture.side) == WEST)
// 		draw.wall_x = cubed->player.y + perp_wall_dist * cubed->ray.dir_y;
// 	else
// 		draw.wall_x = cubed->player.x + perp_wall_dist * cubed->ray.dir_x;
// 	draw.wall_x -= floor(draw.wall_x);
// 		draw.texture_x = (int)(draw.wall_x * \
// 	(double)cubed->texture.texture[cubed->texture.side].width);
// 	draw.texture_y = 0; // Starts sampling from the top of the texture
// 	draw.text_step = (double)cubed->texture.texture[cubed->texture.side].height / (double)draw.height;
// 	if(draw.start < 0)
// 		draw.texture_y = fabs((double)draw.start) * draw.text_step;
// 	draw_ceiling_and_floor(cubed, &draw, col);
// 	draw_wall_section(cubed, &draw, col); // Draw the wall section
// }


