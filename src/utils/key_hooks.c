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

void	key_down(void *data)
{
	t_cube_data	*cubed = (t_cube_data*)data;

	double move_speed = MOVE_SPEED; // Hareket hızı sabiti
	double rotation_speed = ROTATION_SPEED; // Dönüş hızı sabiti

	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_W))
		move_player(cubed, cubed->player.dir_x * move_speed, cubed->player.dir_y * move_speed);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_S))
		move_player(cubed, -cubed->player.dir_x * move_speed, -cubed->player.dir_y * move_speed);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_A))
		move_player(cubed, cubed->player.dir_y * move_speed, -cubed->player.dir_x * move_speed);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_D))
		move_player(cubed, -cubed->player.dir_y * move_speed, cubed->player.dir_x * move_speed);

	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(cubed, -rotation_speed);
	if (mlx_is_key_down(cubed->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(cubed, rotation_speed);
}

void	key_hooks(t_cube_data *cubed)
{
	mlx_close_hook(cubed->mlx_ptr, close_window, NULL);
	mlx_key_hook(cubed->mlx_ptr, key_press, (void*)cubed);
	//loop_hook better than key hook cause loop_hoop checks holding the key.
	//mlx_loop_hook(data->mlx_ptr, key_press, &cubed);
	mlx_loop_hook(cubed->mlx_ptr, key_down, cubed);
}
