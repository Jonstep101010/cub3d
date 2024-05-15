#include "MLX42.h"
#include "structs.h"
#include <stdio.h>
#include "input.h"

void print_texture_details(mlx_texture_t *texture[4]) {
	if (!texture) {
		printf("No texture data available.\n");
		return;
	}

	for (int i = 0; i < 4; i++) {
		printf("Texture %d: \n", i);
		printf("  Width: %u\n", texture[i]->width);
		printf("  Height: %u\n",texture[i]->height);
		printf("  Bytes per Pixel: %u\n", texture[i]->bytes_per_pixel);
		printf("  Pixel Data Address: %p\n", texture[i]->pixels);
	}
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

void print_parse_player(const t_player *res)
{
	printf("..t_player struct...\n");
	printf("t_parse_res res->p_start");
	printf("res->p_start->x (double)= %f\n", res->x);
	printf("res->p_start->y (double)= %f\n", res->y);
	printf(" res->p_start->dir_nesw (t_direction)= %c\n", res->start_nesw);
	printf(".....t_parse_player struct end...\n\n");
}

void print_parsed_data(const t_cube_data *data, const char *source_file) {
	if (!data || !data->res) {
		printf("No data to display.\n");
		return;
	}

	print_player(&data->player);
	print_parse_player(&data->player);
	printf("Parsed Data from file '%s':\n", source_file);
	printf("Map Width, Type: size_t, Value: %zu\n", data->res->map_width);
	printf("Map Height, Type: size_t, Value: %zu\n", data->res->map_height);

	// Printing plane data
	printf("Plane x coordinate data->player.plane_x = %f\n", data->player.plane_x);
	printf("Plane y coordinate data->player.plane_y = %f\n", data->player.plane_y);

	print_texture_details(data->res->tex);
}


// void debug_raycast(t_cube_data *game, t_dda *dda)
// {
//     printf("Ray Pos: (%f, %f), Ray Dir: (%f, %f)\n", game->player.x, game->player.y, game->ray.dir_x, game->ray.dir_y);
//     printf("Step: (X: %d, Y: %d), Delta: (X: %f, Y: %f)\n", dda->step_x, dda->step_y, game->ray.delta_x, game->ray.delta_y);
//     printf("Map Position: (X: %d, Y: %d), Side: %d\n", dda->map_x, dda->map_y, game->texture_side);

//     if (game->res->map_lines[dda->map_y].y_view[dda->map_x] == '1')
//         printf("Wall hit at: (X: %d, Y: %d)\n", dda->map_x, dda->map_y);
//     else
//         printf("No wall hit yet.\n");
// }
