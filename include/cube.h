#ifndef CUBE_H
# define CUBE_H

# include "structs.h"
# include <stdbool.h>
# include <unistd.h>

typedef struct s_cube_data	t_cube;

void	draw_map(t_cube *game);
void	move_player(t_cube_data *data, double dir_x, double dir_y);
void	debug_raycast(t_cube_data *game, t_dda *dda);
t_dda	dda(t_cube_data *cubed);
void	draw_map(t_cube *game);
void	move_player(t_cube_data *data, double dir_x, double dir_y);
void	calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw);
void	calculate_texture_coordinates(t_cube_data *game, t_draw *draw);
void	calculate_ray_deltas(t_ray *ray);
double	calculate_wall_distance(t_cube_data *cubed);
void	draw_ceiling(mlx_image_t *img, int col, int start, uint32_t color);
void	draw_floor(mlx_image_t *img, int col, int end, uint32_t color);
#endif