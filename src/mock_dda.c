#include "cube.h"
#include <math.h>
#include <stdlib.h>
#include "input.h"
#include "libft.h"


// void debug_raycast(	t_cube_data *cubed;, t_coord *dda) {
//     printf("Ray Pos: (%d, %d), Ray Dir: (%f, %f)\n", game->player.x, game->player.y, game->ray.dir_x, game->ray.dir_y);
//     printf("Step: (X: %d, Y: %d), Delta: (X: %f, Y: %f)\n", dda->step_x, dda->step_y, game->ray.delta_x, game->ray.delta_y);
//     printf("Map Position: (X: %d, Y: %d), Side: %d\n", dda->map_x, dda->map_y, game->wall_side);

//     if (game->map.data[dda->map_y][dda->map_x] == '1')
//         printf("Wall hit at: (X: %d, Y: %d)\n", dda->map_x, dda->map_y);
//     else
//         printf("No wall hit yet.\n");
// }

// void	mock_dda(void)
// {



// 	draw_map(&game);
// }
