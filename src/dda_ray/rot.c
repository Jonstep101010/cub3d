#include "cube.h"
#include "defines.h"
#include "math.h"
#include "structs.h"
#include "input.h"
#include <stdbool.h>

bool check_collision(t_cube_data *data, double next_x, double next_y)
{
	int map_x = (int)next_x;
	int map_y = (int)next_y;
	if (data->res->map_lines[map_y].y_view[map_x] == '1')
		return (true);
	if (data->res->map_lines[(int)(next_y + COLLISION_THRESHOLD)].y_view[map_x] == '1' ||
		data->res->map_lines[(int)(next_y - COLLISION_THRESHOLD)].y_view[map_x] == '1' ||
		data->res->map_lines[map_y].y_view[(int)(next_x + COLLISION_THRESHOLD)] == '1' ||
		data->res->map_lines[map_y].y_view[(int)(next_x - COLLISION_THRESHOLD)] == '1')
		return (true);
	return (false);
}

void move_player(t_cube_data *data, double dir_x, double dir_y)
{
	const double next_x = data->player.x + (dir_x * MOVE_SPEED);
	const double next_y = data->player.y + (dir_y * MOVE_SPEED);

	if (!check_collision(data, next_x, data->player.y))
		data->player.x = next_x;
	if (!check_collision(data, data->player.x, next_y))
		data->player.y = next_y;
	draw_map(data); // Only call draw_map after updating player position
}

void rotate_player(t_cube_data *data, double angle)
{
	t_player *player = &data->player;
	const double old_plane_x = player->plane_x;
	// Precompute the cosine and sine of the rotation angle
	const double cos_rot = cos(angle);
	const double sin_rot = sin(angle);
	// Rotate the direction vector
	const double old_dir_x = player->dir_x;

	player->dir_x = player->dir_x * cos_rot - player->dir_y * sin_rot;
	player->dir_y = old_dir_x * sin_rot + player->dir_y * cos_rot;
	// Rotate the camera plane vector
	player->plane_x = player->plane_x * cos_rot - player->plane_y * sin_rot;
	player->plane_y = old_plane_x * sin_rot + player->plane_y * cos_rot;
	// Redraw the map after rotation
	draw_map(data);
}
