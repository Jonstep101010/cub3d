/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:54:46 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/17 18:48:22 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "str_utils.h"
#include <limits.h>

bool	mixed_space_zero(char *const *lines);

uint8_t	build_map_lines(t_cube_file *file);
bool	map_has_empty_line(t_cube_file *file);

bool	x_contains_invalid_chars(t_cube_file *file);
bool	y_contains_invalid_chars(t_cube_file *file);

uint8_t	parse_player_data(t_map_line *map_lines, t_player *player);
bool	player_next_spaces(t_cube_file *file);

void	player_direction(t_player *player);

// printf("charwidth '%s'\n", &file->map_lines[y].y_view[x]);
static void	setup_flood_fill(t_cube_file *file)
{
	int	y;
	int	x;

	y = file->map_height;
	while (y--)
	{
		x = file->map_width - 1;
		while (file->map_lines[y].y_view[x] == ' ')
		{
			file->map_lines[y].y_view[x] = '1';
			file->map_lines[y].len = x;
			x--;
		}
	}
	file->map_width = 0;
	y = 0;
	while (y < (int)file->map_height)
	{
		if (file->map_lines[y].len > file->map_width)
			file->map_width = file->map_lines[y].len;
		y++;
	}
}
	// printf("map_width '%zu'\n", file->map_width);

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
	if (x_contains_invalid_chars(file) != 0)
		return (1);
	setup_flood_fill(file);
	if (y_contains_invalid_chars(file) != 0)
		return (1);
	if (parse_player_data(file->map_lines, &file->player) != 1)
		return (1);
	if (player_next_spaces(file))
		return (1);
	file->player.start_nesw = idx_strchr(DIRECTIONS,
			file->map_lines[(int)file->player.y].y_view[(int)file->player.x]);
	player_direction(&file->player);
	file->map_lines[(int)file->player.y].y_view[(int)file->player.x] = '0';
	return (0);
}
