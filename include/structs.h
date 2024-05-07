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

typedef struct s_map_line 	t_map_line;
typedef struct s_parse_player
{
	size_t	x;
	size_t	y;
	char	dir_nsew;
}	t_parse_player;

typedef struct s_parse_res
{
	size_t			map_width;
	size_t			map_height;
	mlx_texture_t	*tex[4];
	t_rgb			floor;
	t_rgb			ceiling;
	t_map_line		*map_lines;
	t_parse_player	p_start;
}	t_parse_res;

typedef struct s_cube_data
{
	t_parse_res	*res;
	mlx_t		*mlx_ptr;
	mlx_image_t	*floor;
	mlx_image_t	*ceiling;
	uint8_t	 	unused;
	t_rgb		floor_c;//tmp to merge data structures from incoming changes
	t_rgb		ceil_c;//tmp to merge data structures from incoming changes
}	t_cube_data;

#endif