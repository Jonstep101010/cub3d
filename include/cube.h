#ifndef CUBE_H
# define CUBE_H

# include "structs.h"
# include <stdbool.h>
# include <unistd.h>

// Error messages defined for clarity and ease of maintenance
# define ERR_INVALID_DIR "Error: Invalid initial direction provided."
# define ERR_NO_START_POS "Error: No valid player position found."

typedef struct s_cube_data	t_cube;

void	draw_map(t_cube *game);
void	move_player(t_cube_data *data, double dir_x, double dir_y);
void	debug_raycast(t_cube_data *game, t_dda *dda);
t_dda	dda(t_cube_data *cubed);
typedef struct s_cube_data	t_cube;
void	draw_map(t_cube *game);
void	move_player(t_cube_data *data, double dir_x, double dir_y);
uint32_t	get_pixel_color(uint8_t pixels[4]);
void	calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw);
void	calculate_texture_coordinates(t_cube_data *game, t_draw *draw);
double	calculate_camera_x(int i, int width);
void	calculate_ray_deltas(t_ray *ray);
double	calculate_wall_distance(int texture_side, \
	t_dda dist, double delta_x, double delta_y);
void	draw_ceiling(mlx_image_t *img, int col, int start, uint32_t color);
void	draw_floor(mlx_image_t *img, int col, int end, uint32_t color);
#endif