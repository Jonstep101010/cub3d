#include "get_next_line.h"
#include "input.h"
#include "libft.h"
#include "libutils.h"

bool	check_fc_colors(const char *line, t_cube_file *file);
int		check_textures(const char *line, t_cube_textures *files);

static uint8_t	parse_non_map_line(t_cube_file	*file, bool *map)
{
	int				ii;
	const size_t	len = ft_strlen(*file->line_ptr);
	int				space_idx;

	ii = 0;
	while (*file->line_ptr[ii] && ft_isspace(*file->line_ptr[ii]))
		ii++;
	space_idx = index_of(&*file->line_ptr[ii], ' ', (int)len);
	if (!*file->line_ptr[ii] || *file->line_ptr[ii] == '1')
		*map = true;
	else if (ft_strchr("NESW", **file->line_ptr))
	{
		return (space_idx != 2 || file->tex_wall.set
			|| check_textures(&*file->line_ptr[ii], &file->tex_wall) != 0);
	}
	else if (ft_strchr("FC", **file->line_ptr))
	{
		return (space_idx != 1 || !check_fc_colors(*file->line_ptr, file));
	}
	else
		return (1);
	return (0);
}

uint8_t	parse_non_map(t_cube_file *file, char * const *lines)
{
	bool	map;

	map = false;
	file->line_ptr = lines;
	while (!map && *file->line_ptr)
	{
		if (**file->line_ptr && parse_non_map_line(file, &map) != 0)
		{
			return (1);
		}
		if (!map)
		{
			free(*file->line_ptr);
			file->line_ptr++;
		}
	}
	return (!map
		|| (map && (!file->tex_wall.set
				|| !file->ceiling.set
				|| !file->floor.set))
	);
}
