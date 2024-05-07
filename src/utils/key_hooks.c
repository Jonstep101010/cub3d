#include "MLX42.h"
#include "input.h"
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

void	key_hooks(t_cube_data *data)
{
	mlx_close_hook(data->mlx_ptr, close_window, NULL);
	mlx_key_hook(data->mlx_ptr, key_press, (void*)data);
}
