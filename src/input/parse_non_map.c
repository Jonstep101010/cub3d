#include "get_next_line.h"
#include "input.h"
#include "libft.h"
#include "libutils.h"

bool	check_fc_colors(const char *line, t_cube_file *file);
int		check_textures(const char *line, t_cube_textures *files);

static uint8_t	parse_non_map_line(char *line, t_cube_file	*file, bool *map)
{
	int				ii;
	const size_t	len = ft_strlen(line);

	ii = 0;
	while (line[ii] && ft_isspace(line[ii]))
		ii++;
	file->space_idx = index_of(&line[ii], ' ', len);
	if (!line || !line[ii] || line[ii] == '1')
		*map = true;
	if (!*map)
	{
		if (ft_strchr("NESW", *line) && !file->tex_wall.set
			&& ii + file->space_idx < (int)len)
		{
			if (file->space_idx != 2
				|| !check_textures(&line[ii], &file->tex_wall))
				return (1);
		}
		if (ft_strchr("FC", *line))
		{
			if (!check_fc_colors(line, file))
				return (1);
		}
	}
	return (0);
}

uint8_t	parse_non_map(t_cube_file *file)
{
	bool	map;
	int		i;

	map = false;
	i = 0;
	// iterate over file to get lines
	while (!map && file->lines[i])
	{
		if (parse_non_map_line(file->lines[i], file, &map) != 0)
			return (1);
		i++;
	}
	// on map, stop search and invalidate on missing params
	return (!map || (map
			&& (!file->tex_wall.set || !file->ceiling.set || !file->floor.set)));
}
