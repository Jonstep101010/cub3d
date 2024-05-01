#ifndef INPUT_H
# define INPUT_H

typedef struct s_cube_data t_cube_data;
typedef struct s_rgb t_rgb;
# include <stddef.h>
# include <stdbool.h>
typedef enum e_err
{
	NO_ERR,
	// NO_FILE,
	// NO_MAP,
	MISSING_MAP,
	INVALID_MAP,
	MISSING_PARAM,
	DUPLICATE_PARAM,
	INVALID_PARAM,
	// WRONG_RGB,
	ERR_NO_LEADING_ONE,
	ERR_NO_TRAILING_ONE,
	ERR_SPACE_BETWEEN_ZERO,
	ERR_EMPTY_LINE,
}	t_err;

# define MAP_CHARS "10NSEW "
# define DIRECTIONS "NSEW"

typedef struct s_map_line
{
	char		*line;
	char		*y_view;
	size_t		len;
}   t_map_line;

# include "structs.h"

typedef struct s_parse_fc
{
	bool		set;
	t_rgb		color;
}   t_parse_fc;

typedef struct s_cube_textures
{
	char		*path_north;
	char		*path_south;
	char		*path_west;
	char		*path_east;
	bool		set;
}   t_cube_textures;

typedef struct s_player
{
	size_t	x;
	size_t	y;
	char	dir_nsew;
}  t_player;

typedef struct s_cube_file
{
	char * const	*line_ptr;
	t_cube_textures	tex_wall;
	t_map_line		*map_lines;
	t_parse_fc		floor;
	t_parse_fc		ceiling;
	int 			err;
	size_t			map_height;
	size_t			map_width;
	t_player		player;
}   t_cube_file;

#endif