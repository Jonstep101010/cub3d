#include "defines.h"
#include "structs.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	free_cubed(t_cube_data *cubed);
void	key_hooks(t_cube_data *data);
int		paint_background(t_cube_data *game);
uint8_t	parse_file(t_cube_data *data, const char *path_to_file);

//void	mock_dda();
// int32_t	main(int argc, char **argv)
// {
// 	t_cube_data cubed;

// 	cubed = (t_cube_data) {
// 		.unused = 0,
// 	};
// 	if (argc != 2 || parse_file(&cubed, argv[1]) != 0)
// 		return (EXIT_FAILURE);

// 	//init_struct(&cubed);
// 	// @follow-up utilize again once dda works
// 	cubed.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", false);
// 	cubed.image =  mlx_new_image(cubed->mlx.ptr, WIDTH, HEIGHT);

// 	if (!cubed.mlx_ptr)
// 		return (EXIT_FAILURE);

// 	paint_background(&cubed);

// 	key_hooks(&cubed);
// 	// Run the main loop and terminate on quit.
// 	mlx_loop(cubed.mlx_ptr);
// 	mlx_terminate(cubed.mlx_ptr);

// 	// free all data structures
// 	free_cubed(&cubed);

// 	mock dda function calls
// 	mock_dda();
// 	return (EXIT_SUCCESS);
// }


#include <stdio.h>

// Bu fonksiyon t_cube_data içindeki verileri yazdırmak için kullanılabilir
#include "defines.h"
#include "structs.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	free_cubed(t_cube_data *cubed);
void	key_hooks(t_cube_data *data);
int		paint_background(t_cube_data *game);
uint8_t	parse_file(t_cube_data *data, const char *path_to_file);

//void	mock_dda();
// int32_t	main(int argc, char **argv)
// {
// 	t_cube_data cubed;

// 	cubed = (t_cube_data) {
// 		.unused = 0,
// 	};
// 	if (argc != 2 || parse_file(&cubed, argv[1]) != 0)
// 		return (EXIT_FAILURE);

// 	//init_struct(&cubed);
// 	// @follow-up utilize again once dda works
// 	cubed.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", false);
// 	cubed.image =  mlx_new_image(cubed->mlx.ptr, WIDTH, HEIGHT);

// 	if (!cubed.mlx_ptr)
// 		return (EXIT_FAILURE);

// 	paint_background(&cubed);

// 	key_hooks(&cubed);
// 	// Run the main loop and terminate on quit.
// 	mlx_loop(cubed.mlx_ptr);
// 	mlx_terminate(cubed.mlx_ptr);

// 	// free all data structures
// 	free_cubed(&cubed);

// 	mock dda function calls
// 	mock_dda();
// 	return (EXIT_SUCCESS);
// }


#include <stdio.h>

// Bu fonksiyon t_cube_data içindeki verileri yazdırmak için kullanılabilir
void print_parsed_data(const t_cube_data *data) {
    if (!data || !data->res) {
        printf("No data to display.\n");
        return;
    }

    printf("Parsed Data:\n");
    printf("Map Width: %zu, Map Height: %zu\n", data->res->map_width, data->res->map_height);
    printf("Floor Color: RGB(%u, %u, %u)\n", data->res->floor.r, data->res->floor.g, data->res->floor.b);
    printf("Ceiling Color: RGB(%u, %u, %u)\n", data->res->ceiling.r, data->res->ceiling.g, data->res->ceiling.b);

    // Oyuncu başlangıç pozisyonu ve yönü
    printf("Player Start Position: X=%zu, Y=%zu, Direction=%c\n", data->res->p_start.x, data->res->p_start.y, data->res->p_start.dir_nsew);

    // Texture bilgileri
    for (int i = 0; i < 4; i++) {
        if (data->res->tex[i])
            printf("Texture %d: %p\n", i, (void*)data->res->tex[i]);
    }
}


int main(int argc, char **argv) {
    t_cube_data cubed;

    if (argc != 2 || parse_file(&cubed, argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    // Ayrıştırılan verileri yazdır
    print_parsed_data(&cubed);

    return EXIT_SUCCESS;
}
