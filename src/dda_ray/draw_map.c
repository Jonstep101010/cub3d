/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:00 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/17 15:12:28 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "defines.h"
#include "input.h"

static uint32_t	get_pixel_color(uint8_t rgba[4])
{
	return ((*rgba << 24) | (*(rgba + 1) << 16) \
		| (*(rgba + 2) << 8) | *(rgba + 3));
}
//The draw_wall function draws a vertical slice of a wall on the screen based on the texture coordinates calculated earlier. This function takes into account the texture mapping and the screen boundaries to render the wall segment correctly.
//The draw_wall function uses the texture coordinates to calculate the color of each pixel in the wall segment. It reads the color from the texture image and draws it on the screen.
static void	draw_wall(mlx_image_t *img, t_draw *draw, mlx_texture_t *cur_tex)
{
//	y: This is the current y-coordinate on the screen where the wall slice drawing starts. It is initialized to draw->start, which is the top y-coordinate of the wall slice.
	int			y;
	uint32_t	color;
	int			tex_y;

	y = draw->start;
	while (y < draw->end)
	{
		if (y >= 0 && y < HEIGHT && draw->col >= 0 && draw->col < WIDTH) // ensure that current pixel is in the screen boundaries
		{
			tex_y = (int)draw->texture_y & (cur_tex->height - 1);
		//	 Converts the floating-point texture y-coordinate to an integer, as texture coordinates must be integer values (pixel indices).
//cur_tex-&gt;height is a power of 2, cur_tex-&gt;height - 1 will be a binary number with all bits set to 1 (e.g., if height is 8, height - 1 is 7, which is 0111 in binary).
//he bitwise AND operation effectively constrains the result to be within the range [0, cur_tex-&gt;height - 1].
// ıt will work with only power of 2 textures.

//cur_tex-&gt;height - 1 = 8 - 1 = 7 (binary 0111).
//(int)draw-&gt;texture_y &amp; (cur_tex-&gt;height - 1):
//9 in binary is 1001.
//7 in binary is 0111.1001 &amp; 0111 = 0001 (binary AND operation).
//0001 in decimal is 1.Thus, tex_y will be 1, effectively wrapping around to the beginning of the texture.
//This method works seamlessly for textures of any height, but it is particularly optimized for power of 2 textures.
			color = get_pixel_color(&cur_tex->pixels[(cur_tex->width * tex_y + draw->texture_x) * 4]);
		// get_pixel_color function takes a 4-byte array (representing the RGBA components of a pixel) and combines these components into a single 32-bit integer color value.
		// each pixel in the texture is represented by 4 bytes (RGBA components), so the pixel index is calculated as (cur_tex->width * tex_y + draw->texture_x) * 4.
			mlx_put_pixel(img, draw->col, y, color);
			draw->texture_y += draw->text_step;
			//tex_y variable represents the current y-coordinate in the texture for the pixel being drawn on the screen. It is a floating-point value to allow for fractional steps, ensuring smooth texture mapping.
			//draw->text_step is the step size in the texture for each pixel drawn on the screen. It is calculated as the ratio of the texture height to the height of the wall slice being drawn.

		}
		y++;
	}
}
//draw 1 pixel coloumn
//
static void	draw_column(t_cube_data *game, int col)
{
	t_draw			draw;
	const double	wall_distance = calculate_wall_distance(game);

	draw.col = col;
	draw.height = (int)(HEIGHT / wall_distance); // it creates the height of the wall for 3d effect
	draw.start = game->half_height - draw.height / 2;
	draw.end = draw.start + draw.height; //wall lower point
	if (draw.end > HEIGHT) //burada ekranın alt kısmınını çizerken olusa
		draw.end = HEIGHT;
	calculate_wall_x(game, wall_distance, &draw);
	calculate_texture_coordinates(game, &draw);
	draw_wall(game->image, &draw, game->res->tex[game->texture_side]);
	draw_floor(game->image, draw.col, draw.end, game->res->floor);
	draw_ceiling(game->image, draw.col, draw.start, game->res->ceiling);
}

static inline void	render_column(t_cube *cubed, int column)
{
	//The primary purpose of the expression const double camera_x = 2.0 * column / WIDTH - 1 is to map a screen column to a normalized coordinate on the camera plane, which ranges from -1 to 1. This helps in determining the direction of the ray that will be cast through this particular column on the screen.
	//	2.0 * … : This scaling transforms the normalized value (0 to 1) to the range 0 to 2.
	//	- 1: Shifts the range from [0, 2] to [-1, 1].

	const double	camera_x = ((2.0 * column) / WIDTH) - 1;
	const t_player	*player = &cubed->player;

	cubed->ray.dir_x = player->dir_x + player->plane_x * camera_x;
	cubed->ray.dir_y = player->dir_y + player->plane_y * camera_x;
	calculate_ray_deltas(&cubed->ray);
	draw_column(cubed, column);
}

void	draw_map(t_cube_data *cubed)
{
	int		column;

	column = 0; //every  pixel
	while (column < WIDTH)
	{
		render_column(cubed, column);
		column++;
	}
}
