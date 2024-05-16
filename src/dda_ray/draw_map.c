/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:00 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 13:11:41 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "defines.h"
#include <math.h>
#include <stdio.h>
#include "input.h"

static uint32_t	get_pixel_color(uint8_t rgba[4])
{
	return ((*rgba << 24) | (*(rgba + 1) << 16) \
		| (*(rgba + 2) << 8) | *(rgba + 3));
}

static void	draw_wall(mlx_image_t *img, t_draw *draw, t_parse_res *params)
{
	int			y;
	uint32_t	color;
	int			tex_y;

	y = draw->start;
	while (y < draw->end)
	{
		if (y >= 0 && y < (int)img->height
			&& draw->col >= 0 && draw->col < (int)img->width)
		{
			tex_y = (int)draw->texture_y & (params->cur_tex->height - 1);
			color = get_pixel_color(&params->cur_tex->pixels[
					(params->cur_tex->width * tex_y + draw->texture_x) * 4]);
			mlx_put_pixel(img, draw->col, y, color);
			draw->texture_y += draw->text_step;
		}
		y++;
	}
}

static void	draw_column(t_cube_data *game, int col, double wall_distance)
{
	t_draw		draw;

	draw.col = col;
	draw.height = (int)(HEIGHT / wall_distance);
	draw.start = game->half_height - draw.height / 2;
	draw.end = draw.start + draw.height;
	calculate_wall_x(game, wall_distance, &draw);
	calculate_texture_coordinates(game, &draw);
	game->res->cur_tex = game->res->tex[game->texture_side];
	draw_ceiling(game->image, draw.col, draw.start, game->res->ceiling);
	if (draw.end > HEIGHT)
		draw.end = HEIGHT - 1;
	draw_wall(game->image, &draw, game->res);
	draw_floor(game->image, draw.col, draw.end, game->res->floor);
}

void	draw_map(t_cube_data *cubed)
{
	t_dda	dist;
	int		i;
	double	cam_x;
	double	wall_distance;

	i = 0;
	while (i < WIDTH)
	{
		cam_x = calculate_camera_x(i, WIDTH);
		cubed->ray.dir_x = cubed->player.dir_x + cubed->player.plane_x * cam_x;
		cubed->ray.dir_y = cubed->player.dir_y + cubed->player.plane_y * cam_x;
		calculate_ray_deltas(&cubed->ray);
		dist = dda(cubed);
		wall_distance = calculate_wall_distance(cubed->texture_side, dist, \
					cubed->ray.delta_x, cubed->ray.delta_y);
		draw_column(cubed, i, wall_distance);
		i++;
	}
}
