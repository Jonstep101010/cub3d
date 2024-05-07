#ifndef INPUT_H
# define INPUT_H

#include "MLX42.h"
typedef struct s_cube_data t_cube_data;
typedef struct s_rgb t_rgb;
# include <stddef.h>
# include <stdbool.h>

# define MAP_CHARS "10NSEW "
# define DIRECTIONS "NSEW"

typedef struct s_map_line
{
	char		*y_view;
	size_t		len;
}   t_map_line;

# include "structs.h"

typedef struct s_parse_fc
{
	bool		set;
	t_rgb		color;
}   t_parse_fc;

typedef struct	s_dir_nesw
{
	char			*path;
	mlx_texture_t	*tex;
}	t_dir_nesw;

typedef struct s_cube_textures
{
	t_dir_nesw		dir_nesw[4];
	bool			set;
}   t_cube_textures;

typedef struct s_parse_player
{
	size_t	x;
	size_t	y;
	char	dir_nsew;
}  t_parse_player;

typedef struct s_cube_file
{
	char * const	*line_ptr;
	t_cube_textures	tex_wall;
	t_map_line		*map_lines;
	t_parse_fc		floor;
	t_parse_fc		ceiling;
	size_t			map_height;
	size_t			map_width;
	t_parse_player	player;
}   t_cube_file;

#endif