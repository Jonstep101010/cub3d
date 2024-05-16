/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:56:03 by muhnal            #+#    #+#             */
/*   Updated: 2024/05/16 18:20:06 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "defines.h"

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
	while (end < HEIGHT)
	{
		mlx_put_pixel(img, col, end, color);
		end++;
	}
}
