#ifndef INPUT_H
# define INPUT_H

# include "MLX42.h"
# include <stddef.h>
# include <stdbool.h>
# include "structs.h"

typedef struct s_cube_data	t_cube_data;

# define MAP_CHARS "10NESW "
# define DIRECTIONS "NESW"

typedef struct s_map_line
{
	char		*y_view;
	size_t		len;
}	t_map_line;

typedef struct s_parse_fc
{
	bool		set;
	uint32_t	color;
}	t_parse_fc;

typedef struct s_cube_textures
{
	struct
	{
		char			*path;
		mlx_texture_t	*tex;
	}					s_dir_nesw[4];
	bool				set;
}	t_cube_textures;

typedef struct s_cube_file
{
	char *const		*line_ptr;
	t_cube_textures	tex_wall;
	t_map_line		*map_lines;
	t_parse_fc		floor;
	t_parse_fc		ceiling;
	size_t			map_height;
	size_t			map_width;
	t_player		player;
}	t_cube_file;

#endif