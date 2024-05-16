/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:00 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 18:15:21 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "defines.h"
#include "input.h"

static uint32_t	get_pixel_color(uint8_t rgba[4])
{
	return ((*rgba << 24) | (*(rgba + 1) << 16) \
		| (*(rgba + 2) << 8) | *(rgba + 3));
}

static void	draw_wall(mlx_image_t *img, t_draw *draw, mlx_texture_t *cur_tex)
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
			tex_y = (int)draw->texture_y & (cur_tex->height - 1);
			color = get_pixel_color(&cur_tex->pixels[
					(cur_tex->width * tex_y + draw->texture_x) * 4]);
			mlx_put_pixel(img, draw->col, y, color);
			draw->texture_y += draw->text_step;
		}
		y++;
	}
}

static void	draw_column(t_cube_data *game, int col)
{
	t_draw			draw;
	const double	wall_distance = calculate_wall_distance(game);

	draw.col = col;
	draw.height = (int)(HEIGHT / wall_distance);
	draw.start = game->half_height - draw.height / 2;
	draw.end = draw.start + draw.height;
	if (draw.end > HEIGHT)
		draw.end = HEIGHT;
	calculate_wall_x(game, wall_distance, &draw);
	calculate_texture_coordinates(game, &draw);
	draw_ceiling(game->image, draw.col, draw.start, game->res->ceiling);
	draw_wall(game->image, &draw, game->res->tex[game->texture_side]);
	draw_floor(game->image, draw.col, draw.end, game->res->floor);
}

static inline void	render_column(t_cube *cubed, int column)
{
	const double	camera_x = 2.0 * column / WIDTH - 1;
	const t_player	*player = &cubed->player;

	cubed->ray.dir_x = player->dir_x + player->plane_x * camera_x;
	cubed->ray.dir_y = player->dir_y + player->plane_y * camera_x;
	calculate_ray_deltas(&cubed->ray);
	draw_column(cubed, column);
}

void	draw_map(t_cube_data *cubed)
{
	int		column;

	column = 0;
	while (column < WIDTH)
	{
		render_column(cubed, column);
		column++;
	}
}
