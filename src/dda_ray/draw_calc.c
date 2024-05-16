/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:58:51 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 17:51:03 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "cube.h"
#include <math.h>

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

double	calculate_wall_distance(t_cube *cubed)
{
	const t_dda	dist = dda(cubed);

	if (cubed->texture_side == E || cubed->texture_side == W)
		return (dist.x - cubed->ray.delta_x);
	return (dist.y - cubed->ray.delta_y);
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
