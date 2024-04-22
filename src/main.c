#include "cubed.h"
#include "MLX42.h"

// move to header
# define WIDTH 1280
# define HEIGHT 720

int	main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

	t_cube_data cubed;
    (void)cubed;

    // parse user input
	// initialize_input(argc, argv, &cubed);
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
    (void)mlx;

	// if (!mlx)
	// 	exit(EXIT_FAILURE);
	// img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(mlx, img, 0, 0);

    // handle key hooks
	// hooks(&cubed);
    // execute maps
    // run loop
	// mlx_loop(mlx);
	return (0);
}
