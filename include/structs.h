#ifndef STRUCTS_H
# define STRUCTS_H
# include "MLX42.h"
# include <stdint.h>

// data structures from dda
typedef struct s_dda_coord
{
	int			map_x; //player position copied from player position.
	int			map_y; //player position copied from player position
	double		x;
	double		y;
	int			step_x;
	int			step_y;
}t_dda;

typedef struct s_ray
{
	double		delta_x;
	double		delta_y;
	double		dir_x;
	double		dir_y;
	int			len;
} t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		starting_posx;  ///player position
	double		starting_posy;  ////player position
	double		dir_x;
	double		dir_y;
	int			player_start_dir; //playerın BASLAMA YONU
} t_player;

typedef struct s_texture
{
	mlx_texture_t	texture[4];       // Image data for texture
	xpm_t			*xpm[4];
	int				side;
} t_texture;

typedef struct s_draw
{
	int 	height; // Çizilecek texture yüksekliği
	int 	start;      // Çizime başlanacak y koordinatı
	int 	end;        // Çizim bitirilecek y koordinatı
	int 	texture_x;   // Texture x koordinatı
	double	texture_y; // Texture y koordinatı adımı
	double	wall_x;   // Duvarın x koordinatı
	double	text_step;
} t_draw;

// main data structures 
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

	// merged data from dda
	t_rgb			floor_c;//tmp to merge data structures from incoming changes
	t_rgb			ceil_c;//tmp to merge data structures from incoming changes
	mlx_image_t		*image;
	t_player		player;
	t_texture		texture;
	t_ray			ray;
	int				numRays;
	double			plane_x;
	double			plane_y;
}	t_cube_data;

#endif