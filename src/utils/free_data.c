#include "MLX42.h"
#include "input.h"
#include <stdlib.h>

void	free_cubed(t_cube_data *cubed)
{
	int i;

	i = -1;
	while (++i < 4)
		mlx_delete_texture(cubed->res->tex[i]);
	// handle errors in parsing as well, free all mallocs (sep func)
	i = -1;
	while (++i <= (int)cubed->res->map_height)
		free(cubed->res->map_lines[i].y_view);
	free(cubed->res->map_lines);
	free(cubed->res);
}
