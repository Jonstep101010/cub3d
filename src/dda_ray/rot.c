/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:58:27 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 01:26:19 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "defines.h"
#include "structs.h"
#include "input.h"
#include "utils.h"

bool	check_collision(t_cube_data *data, double next_x, double next_y)
{
	const int			map_x = (int)next_x;
	const int			map_y = (int)next_y;
	const t_map_line	*map_line = data->res->map_lines;

	return (
		map_line[map_y].y_view[map_x] == '1'
		|| map_line[(int)(next_y + COLLISION_THRESHOLD)].y_view[map_x] == '1'
		|| map_line[(int)(next_y - COLLISION_THRESHOLD)].y_view[map_x] == '1'
		|| map_line[map_y].y_view[(int)(next_x + COLLISION_THRESHOLD)] == '1'
		|| map_line[map_y].y_view[(int)(next_x - COLLISION_THRESHOLD)] == '1'
	);
}

void	move_player(t_cube_data *data, double dir_x, double dir_y)
{
	const double	next_x = data->player.x + (dir_x * MOVE_SPEED);
	const double	next_y = data->player.y + (dir_y * MOVE_SPEED);

	if (!check_collision(data, next_x, data->player.y))
		data->player.x = next_x;
	if (!check_collision(data, data->player.x, next_y))
		data->player.y = next_y;
	draw_map(data);
}

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
