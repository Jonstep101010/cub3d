#include "input.h"
#include "libft.h"

static bool	x_delim_walls(char *map_line,
	bool *wall_west, bool *wall_east)
{
	int	ii;

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
	while (file->map_lines[i].y_view && i < file->map_height)
	{
		x_wall_west = false;
		x_wall_east = false;
		if (!x_delim_walls(file->map_lines[i].y_view,
				&x_wall_west, &x_wall_east))
			return (true);
		if (!x_wall_west || !x_wall_east)
			return (true);
		i++;
	}
	return (false);
}

static bool	y_delim_walls(t_cube_file *file, size_t x,
	bool *wall_north, bool *wall_south)
{
	size_t	y;

	y = 0;
	while (y < file->map_height)
	{
		if (!ft_strchr(MAP_CHARS, file->map_lines[y].y_view[x]))
			return (true);
		if (file->map_lines[y].y_view[x] == '1' && !*wall_north)
			*wall_north = true;
		else if (!*wall_north
			&& ((file->map_lines[y].y_view[x] == '0'
					|| ft_strchr(DIRECTIONS, file->map_lines[y].y_view[x]))))
			return (printf("Player not enclosed by walls\n"), false);
		y++;
	}
	while (--y > 0)
	{
		if (file->map_lines[y].y_view[x] == '1' && !*wall_south)
			*wall_south = true;
		else if (!*wall_south && ft_strchr("0NESW",
				file->map_lines[y].y_view[x]) && x < file->map_lines[y].len)
			return (printf("Player not enclosed by walls\n"), false);
	}
	return (true);
}

bool	y_contains_invalid_chars(t_cube_file *file)
{
	size_t	x;
	bool	y_wall_north;
	bool	y_wall_south;

	x = 0;
	while (x < file->map_width)
	{
		y_wall_north = false;
		y_wall_south = false;
		if (!y_delim_walls(file, x, &y_wall_north, &y_wall_south))
			return (true);
		if (!y_wall_north || !y_wall_south)
			return (true);
		x++;
	}
	return (false);
}
