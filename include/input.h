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

typedef struct s_cube_file
{
	char		*path_north;
	char		*path_south;
	char		*path_west;
	char		*path_east;
	t_map_line	*map_lines;
	t_rgb		floor_color;
	t_rgb		ceiling_color;
	int 		err;
	int			fd;
	int			map_height;
	int			map_width;
	bool		has_player;
	int			player_x;
	int			player_y;
}   t_cube_file;

#endif