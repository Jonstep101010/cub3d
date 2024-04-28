#include "get_next_line.h"
#include "input.h"
#include "libft.h"
#include "libutils.h"

bool	check_fc_colors(const char *line, t_cube_file *file);
int		check_textures(const char *line, t_cube_textures *files);

static uint8_t	parse_non_map_line(t_cube_file	*file, bool *map)
{
	int				ii;
	const size_t	len = ft_strlen(*file->lines);

	ii = 0;
	while (*file->lines[ii] && ft_isspace(*file->lines[ii]))
		ii++;
	file->space_idx = index_of(&*file->lines[ii], ' ', (int)len);
	if (!*file->lines || !*file->lines[ii] || *file->lines[ii] == '1')
		*map = true;
	if (!*map)
	{
		if (ft_strchr("NESW", **file->lines))
		{
			if (file->space_idx != 2 || file->tex_wall.set
				|| check_textures(&*file->lines[ii], &file->tex_wall) != 0)
				return (1);
		}
		else if (ft_strchr("FC", **file->lines))
		{
			if (file->space_idx != 1 || !check_fc_colors(*file->lines, file))
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

uint8_t	parse_non_map(t_cube_file *file)
{
	bool	map;

	map = false;
	file->original_lines = file->lines;
	// iterate over file to get lines
	while (!map && *file->lines)
	{
		if (**file->lines && parse_non_map_line(file, &map) != 0)
		{
			arr_free(file->lines);
			return (1);
		}
		if (!map)
		{
			free(*file->lines);
			file->lines++;
		}
	}
	// on map, stop search and invalidate on missing params
	return (!map || (map
			&& (!file->tex_wall.set || !file->ceiling.set || !file->floor.set)));
}
