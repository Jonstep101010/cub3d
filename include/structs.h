/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:46:18 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/16 18:46:27 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42.h"
# include <stdint.h>

typedef enum e_direction
{
	N,
	E,
	S,
	W,
}	t_direction;

typedef struct s_dda_coord
{
	int			map_x;
	int			map_y;
	double		x;
	double		y;
	int			step_x;
	int			step_y;
}	t_dda;

typedef struct s_ray
{
	double		delta_x;
	double		delta_y;
	double		dir_x;
	double		dir_y;
	int			len;
}	t_ray;

/**
 * @brief holds wall drawing data
 * @param height wall height
 * @param start start drawing y coordinate
 * @param end end drawing y coordinate
 * @param texture_x x coordinate of the texture
 * @param texture_y y coordinate of the texture
 * @param wall_x x coordinate of the wall
 */
typedef struct s_draw
{
	int		col;
	int		height;
	int		start;
	int		end;
	int		texture_x;
	double	texture_y;
	double	wall_x;
	double	text_step;
}	t_draw;

typedef struct s_map_line	t_map_line;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	t_direction	start_nesw;
	double		plane_x;
	double		plane_y;
}	t_player;

/**
 * @brief
 * @param tex [index: north=0, east=1 south=2 west=3]
 */
typedef struct s_parse_res
{
	const size_t	map_width;
	const size_t	map_height;
	mlx_texture_t	*tex[4];
	const uint32_t	floor;
	const uint32_t	ceiling;
	t_map_line		*map_lines;
}	t_parse_res;

typedef struct s_cube_data
{
	t_parse_res		*res;
	mlx_t			*mlx_ptr;
	mlx_image_t		*image;
	t_player		player;
	t_direction		texture_side;
	t_ray			ray;
	int				half_height;
}	t_cube_data;

#endif
