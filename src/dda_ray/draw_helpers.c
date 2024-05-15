/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:56:03 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 01:33:33 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "structs.h"

uint32_t	get_pixel_color(uint8_t *pixels, int tex_width, \
		int tex_x, int tex_y)
{
	int	tex_index;

	tex_index = (tex_y * tex_width + tex_x) * 4;
	return ((pixels[tex_index] << 24) | (pixels[tex_index + 1] << 16) \
		| (pixels[tex_index + 2] << 8) | pixels[tex_index + 3]);
}

double	update_texture_y(double current_texture_y, double text_step)
{
	return (current_texture_y + text_step);
}

void	draw_ceiling(mlx_image_t *img, int col, int start, uint32_t color)
{
	int	y;

	y = 0;
	while (y < start)
	{
		mlx_put_pixel(img, col, y, color);
		y++;
	}
}

void	draw_floor(mlx_image_t *img, int col, int start, uint32_t color)
{
	while (start < (int)img->height)
	{
		mlx_put_pixel(img, col, start, color);
		start++;
	}
}

void	draw_column(mlx_image_t *img, t_draw *draw, int col, t_col_par *params)
{
	draw_ceiling(img, col, draw->start, params->ceiling_color);
	draw_wall(img, draw, col, params);
	draw_floor(img, col, draw->end, params->floor_color);
}
