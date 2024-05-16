/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:58:51 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 12:53:06 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "cube.h"

void	calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw)
{
	if (game->texture_side == W || game->texture_side == E)
		draw->wall_x = game->player.y + wall_distance * game->ray.dir_y;
	else
		draw->wall_x = game->player.x + wall_distance * game->ray.dir_x;
	draw->wall_x -= floor(draw->wall_x);
}

void	calculate_texture_coordinates(t_cube_data *game, t_draw *draw)
{
	draw->texture_x = (int)(draw->wall_x * \
		(double)game->res->tex[game->texture_side]->width);
	draw->texture_y = 0;
	draw->text_step = (double)game->res-> \
		tex[game->texture_side]->height / draw->height;
	if (draw->start < 0)
	{
		draw->texture_y = -draw->start * draw->text_step;
		draw->start = 0;
	}
}

double	calculate_wall_distance(int texture_side, \
	t_dda dist, double delta_x, double delta_y)
{
	if (texture_side == E || texture_side == W)
		return (dist.x - delta_x);
	return (dist.y - delta_y);
}

double	calculate_camera_x(int i, int width)
{
	return (2 * i / (double)width - 1);
}

void	calculate_ray_deltas(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_x = INFINITY;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = INFINITY;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}
