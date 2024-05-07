#include "input.h"
#include "libft.h"
#include <limits.h>

bool	mixed_space_zero(char * const *lines);

uint8_t	build_map_lines(t_cube_file *file);
bool	map_has_empty_line(t_cube_file *file);

bool	x_contains_invalid_chars(t_cube_file *file);
bool	y_contains_invalid_chars(t_cube_file *file);

uint8_t	parse_player_data(t_map_line *map_lines, t_parse_player *player);
bool	player_next_spaces(t_cube_file *file);

uint8_t	parse_map(t_cube_file *file)
{
	if (mixed_space_zero(file->line_ptr) != 0)
		return (1);
	if (!ft_strchr(*file->line_ptr, '1'))
		return (1);
	if (build_map_lines(file) != 0)
		return (1);
	if (map_has_empty_line(file))
		return (1);
	if (x_contains_invalid_chars(file) != 0
		|| y_contains_invalid_chars(file) != 0)
		return (1);
	if (parse_player_data(file->map_lines, &file->player) != 1)
		return (1);
	if (player_next_spaces(file))
		return (1);
	return (0);
}
