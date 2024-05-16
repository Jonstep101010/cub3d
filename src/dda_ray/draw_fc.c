/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:56:03 by muhnal            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

uint32_t	get_pixel_color(uint8_t rgba[4])
{
	return ((*rgba << 24) | (*(rgba + 1) << 16) \
		| (*(rgba + 2) << 8) | *(rgba + 3));
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
