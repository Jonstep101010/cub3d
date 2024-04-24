#ifndef CUBED_H
# define CUBED_H
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720

# define BPP sizeof(int32_t)

# include "input.h"
typedef struct s_cube_data
{
	t_cube_file	*file;
    uint8_t	 	unused;

}   t_cube_data;
#endif