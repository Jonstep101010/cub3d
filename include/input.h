#ifndef INPUT_H
# define INPUT_H

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

typedef struct s_map_line
{
	char		*line;
	t_line_attr	attr;
}   t_map_line;

# include "structs.h"

typedef struct s_parse_fc
{
	char		*tmp;
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

typedef struct s_cube_file
{
	char		**lines;
	char		**original_lines;
	t_cube_textures	tex_wall;
	// int			space_idx;
	t_map_line	*map_lines;
	t_parse_fc	floor;
	t_parse_fc	ceiling;
	int 		err;
	int			map_height;
	int			map_width;
	int			player_x;
	int			player_y;
}   t_cube_file;

#endif