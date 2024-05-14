#include "cube.h"
#include "math.h"
#include "structs.h"
#include "input.h"

#define ROT_SPEED 0.0174
#define MOVE_SPEED 0.01

void move_player(t_cube_data *data, double dir_x, double dir_y)
{
	double next_x = data->player.x + dir_x;
	double next_y = data->player.y + dir_y;
	int map_x = (int)next_x;
	int map_y = (int)next_y;


	if (data->res->map_lines[map_y].y_view[map_x] == '0')
	{
		data->player.x = next_x;
		data->player.y = next_y;
	}
}


void rotate_player(t_cube_data *data, double angle)
{
	double old_dir_x = data->player.dir_x;
	double old_plane_x = data->plane_x;
	double cos_rot = cos(angle);
	double sin_rot = sin(angle);

	data->player.dir_x = data->player.dir_x * cos_rot - data->player.dir_y * sin_rot;
	data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;

	data->plane_x = data->plane_x * cos_rot - data->plane_y * sin_rot;
	data->plane_y = old_plane_x * sin_rot + data->plane_y * cos_rot;
	draw_map(data);
}
