#include "cubed.h"
#include "structs.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int		paint_background(t_cube_data *game);
uint8_t	parse_file(t_cube_data *data, const char *path_to_file);
int32_t	main(int argc, char **argv)
{
	t_cube_data cubed;

	cubed = (t_cube_data) {
		.unused = 0,
	};
	if (argc != 2 || parse_file(&cubed, argv[1]) != 0)
		return (EXIT_FAILURE);

	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	cubed.mlx = mlx;

	if (!mlx)
		return (EXIT_FAILURE);

	paint_background(&cubed);


	mlx_close_hook(cubed.mlx, close_window, NULL);
	mlx_key_hook(cubed.mlx, key_press, (void*)&cubed);
	// Run the main loop and terminate on quit.
	mlx_loop(mlx);
	mlx_terminate(mlx);

	// free all data structures
	free_cubed(&cubed);
	return (EXIT_SUCCESS);
}
