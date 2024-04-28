#include "input.h"
#include "libft.h"
#include <stdint.h>

bool	parse_player_data(t_map_line *map_lines, t_player *player)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map_lines[y].line)
	{
		x = 0;
		while (map_lines[y].line[x])
		{
			if (ft_strchr("NESW", map_lines[y].line[x]))
			{
				if (!y || !x)
					return (printf("player at 0 index\n"), false);
				if (player->x || player->y)
					return (printf("more than one player found\n"), false);
				player->x = x;
				player->y = y;
				player->dir_nsew = map_lines[y].line[x];
				printf("player found at line %zu, col %zu\n", y, x);
			}
			x++;
		}
		y++;
	}
	return (!((!player->x || !player->y) && printf("no player found\n")));
}
