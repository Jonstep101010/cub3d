#include "input.h"
#include "libft.h"
#include "libutils.h"

bool	mixed_space_zero(char **lines)
{
	size_t	i;
	size_t	ii;

	i = 0;
	while (lines[i])
	{
		ii = 0;
		while (lines[i][ii] && lines[i][ii + 1]) {
			if ((lines[i][ii + 1] == '0' && lines[i][ii] == ' ')
				|| (lines[i][ii] == '0' && lines[i][ii + 1] == ' '))
				return (printf("mixed zero and space\n"), true);
			ii++;
		}
		i++;
	}
	return (false);
}

bool	map_has_empty_line(t_cube_file *file);
bool	x_contains_invalid_chars(t_cube_file *file);
/**
 * @audit moves line_ptr
 */
uint8_t	copy_to_map(t_cube_file *file)
{
	size_t	i;

	if (!ft_strchr(*file->line_ptr, '1') || x_contains_invalid_chars(file) || mixed_space_zero(file->line_ptr))
		return (1);
	// @todo check y (columns)
	while (file->line_ptr[file->map_height]
		&& *file->line_ptr[file->map_height])
			file->map_height++;
	if (file->map_height < 3)
		return (1);
	file->map_lines = ft_calloc(file->map_height + 1, sizeof(t_map_line));
	if (!file->map_lines)// free mem map_lines
		return (1);
	i = 0;
	while (*file->line_ptr && **file->line_ptr)
	{
		file->map_lines[i].line = *file->line_ptr;
		file->map_lines[i].len = ft_strlen(*file->line_ptr);
		while (file->map_lines[i].line[file->map_lines[i].len - 1] == ' ')
			file->map_lines[i].len--;
		if (file->map_lines[i].len > file->map_width)
			file->map_width = file->map_lines[i].len;
		i++;
		file->line_ptr++;
	}
	// caller needs to free map_lines
	return (map_has_empty_line(file));
}

uint8_t	scale_to_widest_line(t_map_line *map_lines, size_t map_width, size_t map_height)
{
	size_t	i;
	size_t	ii;
	char	*scaled_line;

	i = 0;
	while (i <= map_height)
	{
		ii = 0;
		scaled_line = ft_calloc(map_width + 1, sizeof(char));
		if (!scaled_line)
		{
			while (i--)
				free_null(&(map_lines[i].y_view));
			return (2);
		}
		while (ii < map_width)
		{
			if (ii < map_lines[i].len)
				scaled_line[ii] = map_lines[i].line[ii];
			else
				scaled_line[ii] = ' ';
			ii++;
		}
		map_lines[i].y_view = scaled_line;
		i++;
	}
	return (0);
}


bool	y_contains_invalid_chars(t_cube_file *file);
bool	player_next_spaces(t_cube_file *file);
uint8_t	parse_player_data(t_map_line *map_lines, t_player *player);
// @todo make sure map lines do not have any
// invalid characters: 0, 1, ' ', N, S, E, W
// get map grid, delimited by walls, check no empty lines

// member idx should be null if the line is empty
uint8_t	parse_map(t_cube_file *file)
{
	if (copy_to_map(file) != 0)
		return (1);
	if (scale_to_widest_line(file->map_lines, file->map_width, file->map_height) != 0)
		return (1);
	if (y_contains_invalid_chars(file) != 0)
		return (1);
	if (parse_player_data(file->map_lines, &file->player) != 1)
		return (1);
	if (player_next_spaces(file))
		return (1);
	return (0);
}
