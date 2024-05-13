#include "cube.h"
#include "defines.h"
#include "structs.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  // For EXIT_SUCCESS, EXIT_FAILURE macros




void print_texture_details(mlx_texture_t *texture[4]) {
	if (!texture) {
		printf("No texture data available.\n");
		return;
	}

	// mlx_texture_t yapısındaki her bir texture için bilgi yazdırma
	for (int i = 0; i < 4; i++) {
		printf("Texture %d: \n", i);
		printf("  Width: %u\n", texture[i]->width);
		printf("  Height: %u\n",texture[i]->height);
		printf("  Bytes per Pixel: %u\n", texture[i]->bytes_per_pixel);
		printf("  Pixel Data Address: %p\n", texture[i]->pixels);
	}

	// @follow-up
	// Eğer xpm bilgileri varsa onları yazdır
	// for (int i = 0; i < 4; i++) {
	//     if (tex->xpm[i]) {
	//         printf("XPM %d: Description or relevant info here\n", i);
	//         // Burada xpm yapısının içeriklerine göre detaylı bilgileri yazdırabilirsiniz
	//     }
	// }

	// printf("Texture Side: %d\n", tex->side);
}


void print_player(const t_player *player) {
	if (player == NULL) {
		printf("Player data is null.\n");
		return;
	}
	printf("...t_player struct...\n");
	printf("player->x = %f\n", player->x);
	printf("player->y = %f\n", player->y);
	printf("player->dir_x = %f\n", player->dir_x);
	printf("player->dir_y = %f\n", player->dir_y);
   // printf("player->starting_posx = %f\n", player->starting_posx);
   // printf("player->starting_posy = %f\n", player->starting_posy);
	printf(".....t_player struct end...\n\n");
}


void print_parse_player(const t_parse_player *res)
{
	printf("..t_player struct...\n");
	printf("t_parse_res res->p_start");
	printf("res->p_start->x (size_t)= %zu\n", res->x);
	printf("res->p_start->y (size_t)= %zu\n", res->y);
	printf(" res->p_start->dir_nsew (char)= %c\n", res->dir_nsew);
	printf(".....t_parse_player struct end...\n\n");
}


void print_parsed_data(const t_cube_data *data) {
	if (!data || !data->res) {
		printf("No data to display.\n");
		return;
	}

	print_player(&data->player);
	print_parse_player(&data->res->p_start);
	printf("Parsed Data from file '%s':\n", data->source_file);
	printf("Map Width, Type: uint32_t, Value: %zu\n", data->res->map_width);
	printf("Map Height, Type: uint32_t, Value: %zu\n", data->res->map_height);

	    // Printing plane data
    printf("Plane x coordinate data->plane_x = %f\n", data->plane_x);
    printf("Plane y coordinate data->plane_y = %f\n", data->plane_y);

	// Texture verilerini yazdır
	print_texture_details(data->res->tex);
}



void	free_cubed(t_cube_data *cubed);
void	key_hooks(t_cube_data *data);
int		paint_background(t_cube_data *game);
uint8_t	parse_file(t_cube_data *data, const char *path_to_file);

void	key_hook(void *param)
{
	t_cube_data	*cu;

	cu = (t_cube_data *)param;
	if (mlx_is_key_down(cu->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cu->mlx_ptr);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <path_to_cub_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	t_cube_data cubed = {
		.source_file = argv[1],  // Girdi olarak verilen dosya adını kaydet
	};

	if (parse_file(&cubed, argv[1]) != 0) {
		fprintf(stderr, "Failed to parse the .cub file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	cubed.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	cubed.image = mlx_new_image(cubed.mlx_ptr, WIDTH, HEIGHT);
		if (mlx_image_to_window(cubed.mlx_ptr, cubed.image, 0, 0) == -1)
	{
		mlx_close_window(cubed.mlx_ptr);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
		draw_map(&cubed);

	mlx_loop_hook(cubed.mlx_ptr, key_hook , &cubed);
	mlx_loop(cubed.mlx_ptr);


	//print_parsed_data(&cubed);

	free_cubed(&cubed);
	mlx_terminate(cubed.mlx_ptr);

	return EXIT_SUCCESS;  // Program başarılı bir şekilde tamamlandı
}