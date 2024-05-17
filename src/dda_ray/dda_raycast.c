/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:05:50 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/17 13:03:23 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//step_x +1 represent left move; multiplier
//step_x -1 represent right move;
//step_y +1 represent down move;
//step_y -1 represent up move;

//			N -Y
//			|
//			|
//			|
//		|	S +Y

//	W -X -----	E +X

#include "input.h"

static void	wall_collision(t_cube_data *cubed, t_dda *dda)
{
	while (true)
	{
		if (dda->x < dda->y) // we always choose the shorter delta_x bec precise
		{
			dda->x += cubed->ray.delta_x;
			dda->map_x += dda->step_x; //move in the map grid x direction step_x. if step_x is -1 then move left if +1 move right
			if (cubed->ray.dir_x > 0) //moving right so the wall is on the left
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
		if (cubed->res->map_lines[dda->map_y].y_view[dda->map_x] == '1') //map_y map_x grid is wall
			break ;
	}
}
//Positive Direction (dir_x > 0 or dir_y > 0)
//When the ray is moving in the positive direction (right for x, down for y), the next grid line is at the current grid coordinate plus one. This is because we are moving forward towards the next grid boundary.

//Negative Direction (dir_x < 0 or dir_y < 0)
//When the ray is moving in the negative direction (left for x, up for y), the next grid line is already behind the player’s current position within the current grid cell. Therefore, we only need to measure how far back within the current cell the player is.

//here we choose the step size wihch can be -1 +1

		//(cubed->player.x - dda->map_x): This part calculates the fractional distance from the player’s current position within the grid cell to the next vertical grid line.
		//For example, if cubed->player.x is 1.5 and dda->map_x is 1, then cubed->player.x - dda->map_x equals 0.5. This means the player is halfway current grid cell.

		//cubed->ray.delta_x represents the distance the ray needs to travel along the x-axis to move from one vertical grid line to the next.
		//Multiplying the fractional distance by cubed->ray.delta_x scales this fraction to the actual distance the ray needs to travel to reach the next vertical grid line.
static void	initialize_dda(t_cube_data *cubed, t_dda *dda)
{
	dda->map_x = (int)(cubed->player.x);
	dda->map_y = (int)(cubed->player.y);
	dda->step_x = 1;
	dda->step_y = 1;
	if (cubed->ray.dir_x < 0) //moving left
	{
		dda->step_x = -1; //steps should be minus
		dda->x = (cubed->player.x - dda->map_x) * cubed->ray.delta_x;
	//	cubed->player.x - dda->map_x: This gives the fractional part of the player’s x-position within the current grid cell.
	//	For example, if the player’s x-coordinate is 2.3, then cubed->player.x - dda->map_x equals 0.3. This means the player is 0.3 units away from the left edge of the current cell.
	//	cubed->ray.delta_x: This gives the distance the ray needs to travel along the x-axis to move from one vertical grid line to the next.


	}
	else //moving right
		dda->x = (dda->map_x + 1.0 - cubed->player.x) * cubed->ray.delta_x;
		//The player’s current x-coordinate ex. 2.3 units.
		//The x-coordinate of the next vertical grid line ex. 2.
		//Next Vertical Grid Line: dda->map_x + 1.0 = 2 + 1.0 = 3.0 units. This gives the x-coordinate of the next vertical grid line (right edge of the current cell).

		//Distance to the Next Vertical Grid Line:
		//dda->map_x + 1.0 - cubed->player.x = 3.0 - 2.3 = 0.7
		//This gives the distance from the player’s current position (2.3) to the next vertical grid line at 3.0.
	if (cubed->ray.dir_y < 0)
	{
		dda->step_y = -1;
		dda->y = (cubed->player.y - dda->map_y) * cubed->ray.delta_y;
	}
	else
		dda->y = (dda->map_y + 1.0 - cubed->player.y) * cubed->ray.delta_y;
}

t_dda	dda(t_cube_data *cubed)
{
	t_dda	dda;

	initialize_dda(cubed, &dda);
	wall_collision(cubed, &dda);
	return (dda);
}
