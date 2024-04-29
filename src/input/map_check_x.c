#include "input.h"
#include "libft.h"

static bool	x_delim_walls(char *map_line,
	bool *wall_west, bool *wall_east)
{
	size_t	ii;

	ii = 0;
	while (map_line[ii])
	{
		if (!ft_strchr(MAP_CHARS, map_line[ii]))
			return (true);
		if (map_line[ii] == '1' && !*wall_west)
			*wall_west = true;
		else if (!*wall_west
			&& (map_line[ii] == '0' || ft_strchr(DIRECTIONS, map_line[ii])))
			return (printf("Player not enclosed by walls\n"), false);
		ii++;
	}
	while (--ii > 0)
	{
		if (map_line[ii] == '1' && !*wall_east)
			*wall_east = true;
		else if (!*wall_east
			&& (map_line[ii] == '0' || ft_strchr(DIRECTIONS, map_line[ii])))
			return (printf("Player not enclosed by walls\n"), false);
	}
	return (true);
}

bool	x_contains_invalid_chars(t_cube_file *file)
{
	size_t	i;
	bool	x_wall_west;
	bool	x_wall_east;

	i = 0;
	while (file->line_ptr[i])
	{
		x_wall_west = false;
		x_wall_east = false;
		if (!x_delim_walls(file->line_ptr[i], &x_wall_west, &x_wall_east))
			return (true);
		if (!x_wall_west || !x_wall_east)
			return (true);
		i++;
	}
	return (false);
}
