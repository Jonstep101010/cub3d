#include "input.h"
#include "libft.h"
#include "libutils.h"

static uint8_t	set_map_size(t_cube_file *file)
{
	size_t	line_len;

	while (file->line_ptr[file->map_height])
	{
		if (ft_strchr(file->line_ptr[file->map_height], '\t'))
			return (1);
		line_len = ft_strlen(file->line_ptr[file->map_height]);
		if (line_len < 3)
			return (1);
		file->map_height++;
	}
	return (file->map_height < 3);
}

static uint8_t	copy_to_map(t_cube_file *file)
{
	size_t	i;

	if (set_map_size(file) != 0)
		return (1);
	file->map_lines = ft_calloc(file->map_height + 1, sizeof(t_map_line));
	if (!file->map_lines)
		return (1);
	i = 0;
	while (*file->line_ptr)
	{
		file->map_lines[i].line = *file->line_ptr;
		i++;
		file->line_ptr++;
	}
	free_null(&file->lines);
	return (0);
}

uint8_t	parse_player_data(t_map_line *map_lines, t_player *player);
// @todo make sure map lines do not have any invalid characters: 0, 1, ' ', N, S, E, W

// member idx should be null if the line is empty
uint8_t	parse_map(t_cube_file *file)
{
	if (copy_to_map(file) != 0)
		return (1);
	if (parse_player_data(file->map_lines, &file->player) != 1)
		return (1);
	return 0;

}
