
#include "structs.h"
#include "cube.h"
#include <math.h>
//rayin duvara carptigi noktayi hesaplar
void	calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw)
{
	/// If the ray hits the east (E) or west (W) wall, Y-directional components are used to calculate the X-coordinate of the wall: ? why
// because the east and west walls are vertical, and the point of intersection with these walls depends on the distance the ray travels along the Y-axis.

	if (game->texture_side == W || game->texture_side == E)
		draw->wall_x = game->player.y + (wall_distance * game->ray.dir_y); //
	else //degilse s ve e ise x koordinatini hesaplamak icin x i kullanir
		draw->wall_x = game->player.x + (wall_distance * game->ray.dir_x);
	draw->wall_x -= floor(draw->wall_x);
	// We only take the fractional part. When calculating the floor part, subtracting it reveals the integer part which represents the position of the wall. The fractional part indicates...
	// For example, if the value of draw-&gt;wall_x is 0.3, it means we need to use 30% of this texture tile. Since the texture is unit-sized, the integer part is not necessary for texture mapping. The integer part only provides general coordinates which are unnecessary for computation.// For instance, if draw-&gt;wall_x is 5.3, it actually indicates that the wall is 5 units ahead. However, only the 0.3 part is relevant for texture coordinates.
}


//duvar dokusunun (texture) ekranda nasıl görüntüleneceğini belirlemek için doku koordinatlarını hesaplar.bu  fonks, çarpışma noktasının doku üzerindeki X ve Y koordinatlarını hesaplar ve doku üzerinde hangi kısmın ekranda gösterileceğini belirler.

//Calculating texture_x

//	The collision point draw->wall_x is scaled to the texture’s width to find the appropriate column of the texture to use.
//	This ensures that the correct part of the texture is used for the corresponding wall segment.

//Calculating text_step

//		By dividing the texture’s height by the wall segment’s height (draw->height), we determine how much of the texture corresponds to each pixel line of the wall segment.
//		This scaling ensures the texture is properly mapped onto the wall segment regardless of its height.

//Adjusting for Negative draw->start

//	If draw->start is negative, part of the wall segment is off-screen (above the viewport).
//	We adjust draw->texture_y to skip the corresponding part of the texture, so the top of the texture aligns with the top of the screen.

void	calculate_texture_coordinates(t_cube_data *game, t_draw *draw)
{

	draw->texture_x = (int)(draw->wall_x * (double)game->res->tex[game->texture_side]->width);
//Meaning: The x-coordinate on the texture to start drawing from.
//	Mathematical Calculation:
//	Draw->wall_x is multiplied by the width of the texture (game->res->tex[game->texture_side]->width) to get the exact position on the texture.
//	This converts the fractional wall hit position to a pixel position on the texture.
//	The result is cast to an integer because texture coordinates are in pixel values.

	draw->texture_y = 0;
	draw->text_step = (double)game->res-> tex[game->texture_side]->height / draw->height;
//Meaning: This value represents how much to step in the texture for each pixel drawn on the screen.
//	•	Mathematical Calculation:
//	•	The height of the texture (game->res->tex[game->texture_side]->height) is divided by the height of the wall slice (draw->height).
//	•	This gives the step size for moving through the texture as you draw the column of pixels.


	if (draw->start < 0)
	{
		draw->texture_y = -draw->start * draw->text_step;
		draw->start = 0;
	}
	//	•	Meaning and Purpose:
	//	Sometimes, the calculated draw->start might be less than 0, indicating that part of the wall slice is above the screen.
	//	If draw->start < 0, adjust draw->texture_y to skip the invisible part of the texture.
	//	The negative draw->start value is multiplied by draw->text_step to calculate how far into the texture we should start.
	//	draw->start is then set to 0 to ensure we start drawing from the top of the screen.
}
// computes the distance from the player’s position to the point where the ray hits the wall. This distance is necessary for rendering the wall segment correctly on the screen.
double	calculate_wall_distance(t_cube *cubed)
{
	const t_dda	dist = dda(cubed);

//which direction the wall we calculate this coord delta
//	•	dist.x: This is the distance the ray has traveled along the x-axis to hit the wall.
//	•	cubed->ray.delta_x: This is the distance the ray travels from one vertical grid line to the next.
//	•	Mathematical Logic: Subtracting cubed->ray.delta_x from dist.x gives the correct distance to the wall, as dist.x includes an additional step taken in the DDA algorithm.
	if (cubed->texture_side == E || cubed->texture_side == W)
		return (dist.x - cubed->ray.delta_x);
	return (dist.y - cubed->ray.delta_y);

//The DDA algorithm works by stepping through the grid in small increments, checking at each step if a wall has been hit. The dist.x and dist.y values represent the cumulative distances the ray has traveled along the x and y axes, respectively.
//		When the ray hits an East or West wall, the distance traveled along the x-axis (dist.x) is considered, but it includes an additional step. Thus, subtracting cubed->ray.delta_x corrects this overestimation.
//	Similarly, when the ray hits a North or South wall, the distance traveled along the y-axis (dist.y) is considered, and subtracting cubed->ray.delta_y corrects this overestimation.

}



void	calculate_ray_deltas(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_x = INFINITY;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = INFINITY;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}
// Delta Calculation:
// 	delta_x = |1 / dir_x|: Distance the ray travels along the x-axis to move from one grid cell to the next. 1 represent 1 girp
// 	delta_y = |1 / dir_y|: Distance the ray travels along the y-axis to move from one grid cell to the next.

// Delta X Calculation:
// 	•	If dir_x is positive, the ray is moving to the right; if negative, to the left. The distance to the next x grid line is inversely proportional to dir_x.
// 	•
// delta_x = |1 / dir_x|:

//	•	This ensures that if the ray’s x direction component (dir_x) is small, delta_x is large, meaning the ray takes longer to cross a grid cell in the x direction.