#include "MLX42.h"
#include "structs.h"
#include <stdio.h>

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

void print_parsed_data(const t_cube_data *data) {
	if (!data || !data->res) {
		printf("No data to display.\n");
		return;
	}

	print_player(&data->player);
	print_parse_player(&data->player);
	printf("Parsed Data from file '%s':\n", data->source_file);
	printf("Map Width, Type: size_t, Value: %zu\n", data->res->map_width);
	printf("Map Height, Type: size_t, Value: %zu\n", data->res->map_height);

	// Printing plane data
	printf("Plane x coordinate data->player.plane_x = %f\n", data->player.plane_x);
	printf("Plane y coordinate data->player.plane_y = %f\n", data->player.plane_y);

	print_texture_details(data->res->tex);
}
