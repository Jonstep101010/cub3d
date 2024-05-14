#include "cube.h"
#include "defines.h"
#include "math.h"
#include "structs.h"
#include "input.h"

void move_player(t_cube_data *data, double dir_x, double dir_y)
{
	const double next_x = data->player.x + dir_x;
	const double next_y = data->player.y + dir_y;
	int map_x = (int)next_x;
	int map_y = (int)next_y;

	if (data->res->map_lines[map_y].y_view[map_x] == '0')
	{
		data->player.x = next_x;
		data->player.y = next_y;
	}
	draw_map(data);
}

void rotate_player(t_cube_data *data, double angle)
{
	const double old_dir_x = data->player.dir_x;
	const double old_plane_x = data->player.plane_x;
	const double cos_rot = cos(angle);
	const double sin_rot = sin(angle);

	data->player.dir_x = data->player.dir_x * cos_rot - data->player.dir_y * sin_rot;
	data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;

	data->player.plane_x = data->player.plane_x * cos_rot - data->player.plane_y * sin_rot;
	data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y * cos_rot;
	draw_map(data);
}
