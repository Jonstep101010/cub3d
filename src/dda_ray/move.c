#include "cube.h"
#include "defines.h"
#include "structs.h"
#include "input.h"

static bool	check_collision(t_cube_data *data, double next_x, double next_y)
{
	const int			map_x = (int)next_x;
	const int			map_y = (int)next_y;
	const t_map_line	*map_line = data->res->map_lines;

	return (
		map_line[map_y].y_view[map_x] == '1'
		|| map_line[(int)(next_y + COLLISION_THRESHOLD)].y_view[map_x] == '1'
		|| map_line[(int)(next_y - COLLISION_THRESHOLD)].y_view[map_x] == '1'
		|| map_line[map_y].y_view[(int)(next_x + COLLISION_THRESHOLD)] == '1'
		|| map_line[map_y].y_view[(int)(next_x - COLLISION_THRESHOLD)] == '1'
	);
}

void	move_player(t_cube_data *data, double dir_x, double dir_y)
{
	const double	next_x = data->player.x + (dir_x * MOVE_SPEED);
	const double	next_y = data->player.y + (dir_y * MOVE_SPEED);

	if (!check_collision(data, next_x, data->player.y))
		data->player.x = next_x;
	if (!check_collision(data, data->player.x, next_y))
		data->player.y = next_y;
	draw_map(data);
}
