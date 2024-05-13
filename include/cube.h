#ifndef CUBE_H
# define CUBE_H

# include "structs.h"
# include <stdbool.h>
# include <unistd.h>



// Error messages defined for clarity and ease of maintenance
# define ERR_INVALID_DIR "Error: Invalid initial direction provided."
# define ERR_NO_START_POS "Error: No valid player start position found in the map."

typedef struct s_cube_data t_cube;

void load_texture(t_cube *game, t_texture *texture, const char *file_path);
// cube.h içerisine ekleyin
void draw_map(t_cube *game);

t_dda	dda(t_cube	*game);

#endif