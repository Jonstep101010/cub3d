/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:54:40 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/16 18:54:41 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include <stdint.h>

bool	parse_player_data(t_map_line *map_lines, t_player *player)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map_lines[y].y_view)
	{
		x = 0;
		while (map_lines[y].y_view[x])
		{
			if (ft_strchr(DIRECTIONS, map_lines[y].y_view[x]))
			{
				if (!y || !x)
					return (printf("player at 0 index\n"), false);
				if (player->x || player->y)
					return (printf("more than one player found\n"), false);
				player->x = x;
				player->y = y;
				printf("player found at line %zu, col %zu\n", y, x);
			}
			x++;
		}
		y++;
	}
	return (!((!player->x || !player->y) && printf("no player found\n")));
}

bool	player_next_spaces(t_cube_file *file)
{
	const t_player		*player = &file->player;
	const t_map_line	*map_lines = file->map_lines;
	const int			start_x = player->x;
	const int			start_y = player->y;

	return (player->x + 1 >= map_lines[start_y].len
		|| map_lines[start_y - 1].y_view[start_x] == ' '
		|| map_lines[start_y + 1].y_view[start_x] == ' '
		|| map_lines[start_y].y_view[start_x - 1] == ' '
		|| map_lines[start_y].y_view[start_x + 1] == ' '
		|| map_lines[start_y + 1].y_view[start_x - 1] == ' '
		|| map_lines[start_y + 1].y_view[start_x + 1] == ' '
		|| map_lines[start_y - 1].y_view[start_x - 1] == ' '
		|| map_lines[start_y - 1].y_view[start_x + 1] == ' '
	);
}

void	player_direction(t_player *player)
{
	player->x += 0.5;
	player->y += 0.5;
	if (player->start_nesw == N)
	{
		player->dir_y = -1.0;
		player->plane_x = 0.66;
	}
	else if (player->start_nesw == S)
	{
		player->dir_y = 1.0;
		player->plane_x = -0.66;
	}
	else if (player->start_nesw == E)
	{
		player->dir_x = 1.0;
		player->plane_y = 0.66;
	}
	else if (player->start_nesw == W)
	{
		player->dir_x = -1.0;
		player->plane_y = -0.66;
	}
}
