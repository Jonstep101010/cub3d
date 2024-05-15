#ifndef STRUCTS_H
# define STRUCTS_H
# include "MLX42.h"
# include <stdint.h>

typedef enum e_direction
{
	N,
	E,
	S,
	W,
}	t_direction;
// data structures from dda
typedef struct s_dda_coord
{
	int			map_x; //player position copied from player position.
	int			map_y; //player position copied from player position
	double		x;
	double		y;
	int			step_x;
	int			step_y;
}	t_dda;

typedef struct s_ray
{
	double		delta_x;
	double		delta_y;
	double		dir_x;
	double		dir_y;
	int			len;
}	t_ray;

typedef struct s_draw
{
	int 	height; // wall height
	int 	start;      // start drawing y coordinate
	int 	end;        // end drawing y coordinate
	int 	texture_x;   // Texture x koordinatı
	double	texture_y; // Texture y koordinatı adımı
	double	wall_x;   // Duvarın x koordinatı
	double	text_step;
}	t_draw;

// main data structures
typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct s_map_line 	t_map_line;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	t_direction	start_nesw;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_parse_res
{
	const size_t	map_width;
	const size_t	map_height;
	mlx_texture_t	*tex[4]; //index is the direction of textures..north =0, east=1 south=2 west=3
	const uint32_t	floor;
	const uint32_t	ceiling;
	t_map_line		*map_lines;
}	t_parse_res;

typedef struct s_cube_data
{
	t_parse_res		*res;
	mlx_t			*mlx_ptr;
	// merged data from dda
	mlx_image_t		*image;
	t_player		player;
	t_direction		texture_side;
	t_ray			ray;
	char*			source_file; // for print data
	int				half_height;
}	t_cube_data;

#endif

void debug_raycast(t_cube_data *game, t_dda *dda);
t_dda dda(t_cube_data *cubed);