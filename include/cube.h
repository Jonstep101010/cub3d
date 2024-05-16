/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:43:35 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/16 18:43:36 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "structs.h"
# include <stdbool.h>
# include <unistd.h>

typedef struct s_cube_data	t_cube;

void	draw_map(t_cube *game);

void	calculate_ray_deltas(t_ray *ray);
double	calculate_wall_distance(t_cube_data *cubed);
t_dda	dda(t_cube_data *cubed);

void	calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw);
void	calculate_texture_coordinates(t_cube_data *game, t_draw *draw);
void	draw_ceiling(mlx_image_t *img, int col, int start, uint32_t color);
void	draw_floor(mlx_image_t *img, int col, int end, uint32_t color);
#endif