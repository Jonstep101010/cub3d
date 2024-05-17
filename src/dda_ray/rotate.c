/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:58:27 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/17 10:20:00 by muhnal           ###   ########.fr       */
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

//https://en.wikipedia.org/wiki/Rotation_matrix

    // Rotate the player's direction vector (dir_x, dir_y)
    // Using the 2D rotation matrix:
    // [ cos(angle) -sin(angle) ]   [ old_dir_x ]
    // [ sin(angle)  cos(angle) ] * [ dir_y     ]
    //
    // This results in:
    // new_dir_x = old_dir_x * cos(angle) - dir_y * sin(angle)
    // new_dir_y = old_dir_x * sin(angle) + dir_y * cos(angle)
    //
    // Explanation:
    // The direction vector is rotated by 'angle' radians around the origin (0, 0).
    // The cosine and sine values of the angle are used to calculate the new coordinates
    // of the direction vector after rotation.
 //   player->dir_x = player->dir_x * cos_rot - player->dir_y * sin_rot;
  //  player->dir_y = old_dir_x * sin_rot + player->dir_y * cos_rot;

    // Rotate the camera plane vector (plane_x, plane_y)
    // Using the same 2D rotation matrix:
    // [ cos(angle) -sin(angle) ]   [ old_plane_x ]
    // [ sin(angle)  cos(angle) ] * [ plane_y     ]
    //
    // This results in:
    // new_plane_x = old_plane_x * cos(angle) - plane_y * sin(angle)
    // new_plane_y = old_plane_x * sin(angle) + plane_y * cos(angle)
    //
    // Explanation:
    // The camera plane vector is rotated by 'angle' radians around the origin (0, 0).
    // The cosine and sine values of the angle are used to calculate the new coordinates
    // of the camera plane vector after rotation.
  //  player->plane_x = player->plane_x * cos_rot - player->plane_y * sin_rot;
    //player->plane_y = old_plane_x * sin_rot + player->plane_y * cos_rot;

    // Redraw the map to reflect the player's new orientation
    // This updates the visual representation of the player's view direction