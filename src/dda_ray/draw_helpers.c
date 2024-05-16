/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:56:03 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 11:54:46 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

uint32_t	get_pixel_color(uint8_t *pixels, int tex_width, \
		int tex_x, int tex_y)
{
	int	tex_index;

	tex_index = (tex_y * tex_width + tex_x) * 4;
	return ((pixels[tex_index] << 24) | (pixels[tex_index + 1] << 16) \
		| (pixels[tex_index + 2] << 8) | pixels[tex_index + 3]);
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

void	draw_floor(mlx_image_t *img, int col, int end, uint32_t color)
{
	while (end < (int)img->height)
	{
		mlx_put_pixel(img, col, end, color);
		end++;
	}
}
