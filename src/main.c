#include "MLX42.h"
#include "cube.h"
#include "defines.h"
#include "structs.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	free_cubed(t_cube_data *cubed);
void	key_hooks(t_cube_data *data);
uint8_t	parse_file(t_cube_data *data, const char *path_to_file);
void	print_parsed_data(const t_cube_data *data, const char *path_to_file);

int main(int argc, char **argv)
{
	t_cube_data cubed;

	cubed = (t_cube_data){.half_height = HEIGHT / 2,};

	if (argc == 2 && parse_file(&cubed, argv[1]) == 0) {
		cubed.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", false);
		cubed.image = mlx_new_image(cubed.mlx_ptr, WIDTH, HEIGHT);
		if (mlx_image_to_window(cubed.mlx_ptr, cubed.image, 0, 0) == -1)
		{
			mlx_close_window(cubed.mlx_ptr);
			return (printf("%s\n", mlx_strerror(mlx_errno)), EXIT_FAILURE);
		}
		draw_map(&cubed);
		key_hooks(&cubed);
		mlx_loop(cubed.mlx_ptr);
		free_cubed(&cubed);
		mlx_terminate(cubed.mlx_ptr);
		return (EXIT_SUCCESS);
	}
	if (argc != 2)
		printf("Usage: %s <path_to_cub_file>\n", argv[0]);
	else
		printf("Failed to parse the .cub file: %s\n", argv[1]);
	return (EXIT_FAILURE);
}
