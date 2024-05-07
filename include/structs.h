#ifndef STRUCTS_H
# define STRUCTS_H
# include "MLX42.h"
# include <stdint.h>
typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct s_cube_file t_cube_file;
typedef struct s_cube_data
{
	t_cube_file	*file;
	mlx_t		*mlx_ptr;
	mlx_image_t	*floor;
	mlx_image_t	*ceiling;
	uint8_t	 	unused;
}	t_cube_data;

#endif