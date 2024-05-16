/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:00 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 12:09:52 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "defines.h"

void	draw_wall(mlx_image_t *img, t_draw *draw, int col, t_parse_res *params)
{
	double		current_texture_y;
	int			y;
	uint8_t		*pixels;
	uint32_t	color;
	int			tex_y;

	current_texture_y = draw->texture_y;
	y = draw->start;
	pixels = params->cur_tex->pixels;
	while (y < draw->end)
	{
		if (y >= 0 && y < (int)img->height && col >= 0 && col < (int)img->width)
		{
			tex_y = (int)current_texture_y & (params->cur_tex->height - 1);
			color = get_pixel_color(pixels, params->cur_tex->width, \
				draw->texture_x, tex_y);
			mlx_put_pixel(img, col, y, color);
			current_texture_y += draw->text_step;
		}
		y++;
	}
}

void	draw_line_of_texture(t_cube_data *game, int col, double wall_distance)
{
	t_draw		draw;

	draw.height = (int)(HEIGHT / wall_distance);
	draw.start = game->half_height - draw.height / 2;
	draw.end = draw.start + draw.height;
	calculate_wall_x(game, wall_distance, &draw);
	calculate_texture_coordinates(game, &draw);
	if (draw.end >= HEIGHT)
		draw.end = HEIGHT - 1;
	game->res->cur_tex = game->res->tex[game->texture_side];
	draw_column(game->image, &draw, col, game->res);
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
		draw_line_of_texture(cubed, i, wall_distance);
		i++;
	}
}

void	draw_column(mlx_image_t *img, t_draw *draw, int col, t_parse_res *params)
{
	draw_ceiling(img, col, draw->start, params->ceiling);
	draw_wall(img, draw, col, params);
	draw_floor(img, col, draw->end, params->floor);
}
