#include "MLX42.h"
#include "input.h"
#include <stdlib.h>

void	free_cubed(t_cube_data *cubed)
{
	int i;

	i = -1;
	while (++i < 4)
		mlx_delete_texture(cubed->file->tex_wall.dir_nesw[i].tex);
	// handle errors in parsing as well, free all mallocs (sep func)
	i = -1;
	while (++i <= (int)cubed->file->map_height)
		free(cubed->file->map_lines[i].y_view);
	free(cubed->file->map_lines);
	free(cubed->file);
}
