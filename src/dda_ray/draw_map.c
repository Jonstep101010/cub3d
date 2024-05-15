/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:00 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/15 23:02:03 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "defines.h"
#include <math.h>
#include "input.h"
#include "libft.h"

typedef struct s_column_params
{
	mlx_texture_t *texture;
	uint32_t ceiling_color;
	uint32_t floor_color;
} t_col_par;


void	draw_column(mlx_image_t *img, t_draw *draw, int col, t_col_par *params)
{
	int			y;
	int			tex_y;
	uint32_t	color;
	uint8_t	*pixels = params->texture->pixels;
	const int	img_height = (int)img->height;
	const int	img_width = (int)img->width;
	const int	tex_width = params->texture->width;
	const int	tex_height = params->texture->height;

	y = 0;
	while (y < draw->start)
	{
		if (y >= 0 && col >= 0 && col < img_width)
			mlx_put_pixel(img, col, y, params->ceiling_color);
		y++;
	}
	double current_texture_y = draw->texture_y;
	while (y < draw->end)
	{
		if (y >= 0 && y < img_height && col >= 0 && col < img_width)
		{
			tex_y = (int)current_texture_y & (tex_height - 1);
			current_texture_y += draw->text_step;
			int tex_index = (tex_y * tex_width + draw->texture_x) * 4;
			color = (pixels[tex_index] << 24) | (pixels[tex_index + 1] << 16) | (pixels[tex_index + 2] << 8) | pixels[tex_index + 3];
			mlx_put_pixel(img, col, y, color);
		}
		y++;
	}
	while (y < img_height)
	{
		if (y >= 0 && col >= 0 && col < img_width)
			mlx_put_pixel(img, col, y, params->floor_color);
		y++;
	}
}


// void	calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw)
// {
// 	if (game->texture_side == W || game->texture_side == E)
// 		draw->wall_x = game->player.y + wall_distance * game->ray.dir_y;
// 	else
// 		draw->wall_x = game->player.x + wall_distance * game->ray.dir_x;
// 	draw->wall_x -= floor(draw->wall_x);
// }

// void	calculate_texture_coordinates(t_cube_data *game, t_draw *draw)
// {
// 	draw->texture_x = (int)(draw->wall_x * \
// 		(double)game->res->tex[game->texture_side]->width);
// 	draw->texture_y = 0;
// 	draw->text_step = (double)game->res-> \
// 		tex[game->texture_side]->height / draw->height;
// 	if (draw->start < 0)
// 		draw->texture_y = -draw->start * draw->text_step;
// }

// void draw_line_of_texture(t_cube_data *game, int col, double wall_distance)
// {
// 	t_draw draw;

// 	draw.height = (int)(HEIGHT / wall_distance);
// 	draw.start = game->half_height - draw.height / 2;
// 	draw.end = draw.start + draw.height;
// 	calculate_wall_x(game, wall_distance, &draw);
// 	calculate_texture_coordinates(game, &draw);
// 	if (draw.start < 0)
// 	{
// 		draw.texture_y = -draw.start * draw.text_step;
// 		draw.start = 0;
// 	}
// 	if (draw.end >= HEIGHT)
// 		draw.end = HEIGHT - 1;
// 	t_column_params params = { game->res->tex[game->texture_side], game->res->ceiling, game->res->floor };
// 	draw_column(game->image, &draw, col, &params);
// }

// void set_ray_deltas(double dir_x, double dir_y, double *delta_x, double *delta_y)
// {
// 	if (dir_x == 0)
// 		*delta_x = INFINITY;
// 	else
// 		*delta_x = fabs(1 / dir_x);
// 	if (dir_y == 0)
// 		*delta_y = INFINITY;
// 	else
// 		*delta_y = fabs(1 / dir_y);
// }

// double calculate_wall_distance(int texture_side, t_dda dist, double delta_x, double delta_y)
// {
// 	if (texture_side == E || texture_side == W)
// 		return dist.x - delta_x;
// 	else
// 		return dist.y - delta_y;
// }

// void draw_map(t_cube_data *cubed)
// {
// 	t_dda dist;
// 	double cam_x;
// 	int i;
// 	double delta_x, delta_y;
// 	double wall_distance;

// 	ft_memset(cubed->image->pixels, 0x000000FF, WIDTH * HEIGHT);
// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		cam_x = 2 * i / (double)WIDTH - 1;
// 		cubed->ray.dir_x = cubed->player.dir_x + cubed->player.plane_x * cam_x;
// 		cubed->ray.dir_y = cubed->player.dir_y + cubed->player.plane_y * cam_x;
// 		set_ray_deltas(cubed->ray.dir_x, cubed->ray.dir_y, &delta_x, &delta_y);
// 		cubed->ray.delta_x = delta_x;
// 		cubed->ray.delta_y = delta_y;
// 		dist = dda(cubed);
// 		wall_distance = calculate_wall_distance(cubed->texture_side, dist, delta_x, delta_y);
// 		draw_line_of_texture(cubed, i, wall_distance);
// 		i++;
// 	}
// }


