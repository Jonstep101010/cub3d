#ifndef INPUT_H
# define INPUT_H

#include <stddef.h>
#include <stdbool.h>
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
}	t_err;

typedef enum e_line_attr
{
	ERR_NO_LEADING_ONE,
	ERR_NO_TRAILING_ONE,
	ERR_SPACE_BETWEEN_ZERO,
	ERR_OTHER,
	ERR_EMPTY_LINE,
	VALID_LINE,
	WALL_ONLY,
}	t_line_attr;

# define MAP_CHARS "10NSEW "
# define DIRECTIONS "NSEW"

typedef struct s_map_line
{
	char		*line;
	char		*y_view;
	size_t		len;
	t_line_attr	attr;
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
	char			**line_ptr;
	char			**lines;
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