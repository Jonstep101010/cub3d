#include "cubed.h"
#include "input.h"
#include "utils.h"

void	paint_image(mlx_image_t *image, t_rgb color)
{
	const int	width = image->width;
	const int	height = image->height;
	int			x;
	int			y;

	y = -1;
	while (++y < height) {
		x = -1;
		while (++x < width) {
			int index = (y * width + x) * BPP;
			image->pixels[index] = color.r;
			image->pixels[index + 1] = color.g;
			image->pixels[index + 2] = color.b;
			image->pixels[index + 3] = 255;
		}
	}
}

int	paint_background(t_cube_data *game)
{
   	game->ceiling = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT / 2);
   	game->floor = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT / 2);

	if (!game->ceiling || !game->floor)
		return (1);
	paint_image(game->ceiling, game->file->ceiling.color);
	paint_image(game->floor, game->file->floor.color);

	mlx_image_to_window(game->mlx_ptr, game->ceiling, 0, 0);
	mlx_image_to_window(game->mlx_ptr, game->floor, 0, HEIGHT / 2);
	return (0);
}
