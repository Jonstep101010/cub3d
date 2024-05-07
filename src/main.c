#include "cubed.h"
#include "structs.h"
#include "input.h"
#include <stdlib.h>
#include <unistd.h>

void	free_cubed(t_cube_data *cubed);
void	key_hooks(t_cube_data *data);
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

	cubed.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	if (!cubed.mlx_ptr)
		return (EXIT_FAILURE);

	paint_background(&cubed);

	key_hooks(&cubed);
	// Run the main loop and terminate on quit.
	mlx_loop(cubed.mlx_ptr);
	mlx_terminate(cubed.mlx_ptr);

	// free all data structures
	free_cubed(&cubed);
	return (EXIT_SUCCESS);
}
