#ifndef CUBE_H
#define CUBE_H

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800

#include "MLX42.h"
#include "libft.h"
#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Error messages defined for clarity and ease of maintenance
#define ERR_INVALID_DIR "Error: Invalid initial direction provided."
#define ERR_NO_START_POS "Error: No valid player start position found in the map."

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NON
} t_direction;


typedef struct s_dda_coord
{
	int			map_x; //player position copied from player position.
	int			map_y; //player position copied from player position
	double		x;
	double		y;
	int			step_x;
	int			step_y;
}t_dda;



typedef struct s_ray
{
	double		delta_x;
	double		delta_y;
	double		dir_x;
	double		dir_y;
	int			len;

} t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double starting_posx;  ///player position
	double starting_posy;  ////player position
	double		dir_x;
	double		dir_y;
	double		plane_x;	   // playerin x düzlemindeki kendi koordinatı
	double		plane_y;	   // playerin y düzlemindeki kendi koordinatı
	int			player_start_dir; //playerın BASLAMA YONU

} t_player;

typedef struct s_texture
{
	mlx_texture_t	texture[4];       // Image data for texture
	xpm_t			*xpm[4];
	int				side;
} t_texture;

typedef struct s_draw {
	int height; // Çizilecek texture yüksekliği
	int start;      // Çizime başlanacak y koordinatı
	int end;        // Çizim bitirilecek y koordinatı
	int texture_x;   // Texture x koordinatı
	double texture_y; // Texture y koordinatı adımı
	double wall_x;   // Duvarın x koordinatı
	double text_step;
} t_draw;

typedef	struct s_map
{
	char	**map;
	int		map_height;
	int		map_width;
}t_map;

typedef struct s_color
{
	int r;  // red
	int g;  // green
	int b;  // blue
} t_color;

typedef struct s_cube_data
{
	mlx_image_t		*image;
	 mlx_t			*mlx_ptr;
	t_player		player;
	t_map			game_map;
	t_texture		texture; // Textures for each direction
	t_ray			ray;		// Ray dizisi
	int				numRays;		// Ray sayısı
	t_color		floor_c;
	t_color		ceil_c;
} t_cube;

void initialize_textures(t_cube *game);
void load_texture(t_cube *game, t_texture *texture, const char *file_path);
// cube.h içerisine ekleyin
char* get_direction_name(t_direction dir);
void draw_map(t_cube *game);


#endif