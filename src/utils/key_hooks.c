/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:52:58 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/16 18:52:59 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "defines.h"
#include "structs.h"
#include <stdlib.h>

void	free_cubed(t_cube_data *cubed);

static void	close_window(void *param)
{
	free_cubed((t_cube_data *)param);
	exit(EXIT_SUCCESS);
}

static void	key_press(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		close_window(param);
}

void	rotate_player(t_cube_data *data, double angle);
void	move_player(t_cube_data *data, double dir_x, double dir_y);

static void	key_down(void *data)
{
	t_cube_data	*cubed;

	cubed = (t_cube_data *)data;
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_W))
		move_player(cubed, cubed->player.dir_x, cubed->player.dir_y);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_S))
		move_player(cubed, -cubed->player.dir_x, -cubed->player.dir_y);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_A))
		move_player(cubed, cubed->player.dir_y, -cubed->player.dir_x);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_D))
		move_player(cubed, -cubed->player.dir_y, cubed->player.dir_x);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(cubed, -ROTATION_SPEED);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(cubed, ROTATION_SPEED);
}

void	key_hooks(t_cube_data *cubed)
{
	mlx_close_hook(cubed->mlx_ptr, close_window, NULL);
	mlx_key_hook(cubed->mlx_ptr, key_press, (void *)cubed);
	mlx_loop_hook(cubed->mlx_ptr, key_down, cubed);
}
