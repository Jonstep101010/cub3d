#include "input.h"
#include "libft.h"
#include "libutils.h"

static uint8_t	set_map_size(t_cube_file *file)
{
	size_t	line_len;

	while (file->line_ptr[file->map_height]
		&& *file->line_ptr[file->map_height])
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

/**
 * @audit moves line_ptr
 */
static bool	map_has_empty_line(t_cube_file *file)
{
	size_t	i;
	size_t	len;
	bool	split_map;

	i = 0;
	split_map = false;
	while (*file->line_ptr)
	{
		i = 0;
		len = ft_strlen(*file->line_ptr);
		while (i < len && !split_map)
		{
			if (ft_strchr("01NSEW ",  **file->line_ptr))
				split_map = true;
			i++;
		}
		free(*file->line_ptr);
		file->line_ptr++;
	}
	free_null(&file->lines);
	file->line_ptr = NULL;
	return (split_map && printf("split map!\n"));
}

/**
 * @audit moves line_ptr
 */
static uint8_t	copy_to_map(t_cube_file *file)
{
	size_t	i;

	if (set_map_size(file) != 0)// free mem
		return (1);
	file->map_lines = ft_calloc(file->map_height + 1, sizeof(t_map_line));
	if (!file->map_lines)// free mem map_lines
		return (1);
	i = 0;
	while (*file->line_ptr && **file->line_ptr)
	{
		file->map_lines[i].line = *file->line_ptr;
		i++;
		file->line_ptr++;
	}
	// caller needs to free map_lines
	return (map_has_empty_line(file));
}

uint8_t	parse_player_data(t_map_line *map_lines, t_player *player);
// @todo make sure map lines do not have any
// invalid characters: 0, 1, ' ', N, S, E, W
// get map grid, delimited by walls, check no empty lines

// member idx should be null if the line is empty
uint8_t	parse_map(t_cube_file *file)
{
	if (copy_to_map(file) != 0)
		return (1);
	if (parse_player_data(file->map_lines, &file->player) != 1)
		return (1);
	return (0);
}
