#include "cubed.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int32_t	main(void)
{
	t_cube_data cubed;

	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	if (!mlx)
		exit(EXIT_FAILURE);

    mlx_image_t* img = mlx_new_image(mlx, 128, 128);

    // Set the channels of each pixel in our image to the maximum byte value of 255.
    memset(img->pixels, 255, img->width * img->height * BPP);

    // Draw the image at coordinate (0, 0).
    mlx_image_to_window(mlx, img, 0, 0);

    // Run the main loop and terminate on quit.
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}
