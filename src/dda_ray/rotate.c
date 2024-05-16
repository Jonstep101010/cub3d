/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:58:27 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 13:25:16 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "structs.h"
#include <math.h>

/**
 * @brief get new player FOV, update player dir and plane
 */
void	rotate_player(t_cube_data *data, double angle)
{
	const double	old_plane_x = data->player.plane_x;
	const double	cos_rot = cos(angle);
	const double	sin_rot = sin(angle);
	const double	old_dir_x = data->player.dir_x;
	t_player		*player;

	player = &data->player;
	player->dir_x = player->dir_x * cos_rot - player->dir_y * sin_rot;
	player->dir_y = old_dir_x * sin_rot + player->dir_y * cos_rot;
	player->plane_x = player->plane_x * cos_rot - player->plane_y * sin_rot;
	player->plane_y = old_plane_x * sin_rot + player->plane_y * cos_rot;
	draw_map(data);
}
