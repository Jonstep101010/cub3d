#include "input.h"
#include "structs.h"
#include <stdint.h>

static void wall_collision(t_cube_data *cubed, t_dda *dda)
{
	while (true)
	{
		if (dda->x < dda->y)
		{
			dda->x += cubed->ray.delta_x;
			dda->map_x += dda->step_x;
			if (cubed->ray.dir_x > 0)
				cubed->texture_side = E;
			else
				cubed->texture_side = W;
		}
		else
		{
			dda->y += cubed->ray.delta_y;
			dda->map_y += dda->step_y;
			if (cubed->ray.dir_y > 0)
				cubed->texture_side = S;
			else
				cubed->texture_side = N;
		}
		if (cubed->res->map_lines[dda->map_y].y_view[dda->map_x] == '1')
			break ;
	}
}

t_dda	dda(t_cube_data	*cubed)
{
	t_dda	dda;

	dda.map_x = (int)(cubed->player.x);
	dda.map_y = (int)(cubed->player.y);
	dda.step_x = 1;
	dda.step_y = 1;
	if (cubed->ray.dir_x < 0)
	{
		dda.step_x = -1;
		dda.x = (cubed->player.x - dda.map_x) *  cubed->ray.delta_x;
	}
	else
		dda.x = (dda.map_x + 1.0 - cubed->player.x) * cubed->ray.delta_x;
	if (cubed->ray.dir_y < 0)
	{
		dda.step_y = -1;
		dda.y = (cubed->player.y - dda.map_y) *  cubed->ray.delta_y;
	}
	else
		dda.y = (dda.map_y + 1.0 - cubed->player.y) * cubed->ray.delta_y;
	wall_collision(cubed, &dda);
	return(dda);
}
