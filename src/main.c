#include "defines.h"
#include "structs.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  // For EXIT_SUCCESS, EXIT_FAILURE macros




void print_texture_details(const t_texture *tex) {
    if (!tex) {
        printf("No texture data available.\n");
        return;
    }

    // mlx_texture_t yapısındaki her bir texture için bilgi yazdırma
    for (int i = 0; i < 4; i++) {
        printf("Texture %d: \n", i);
        printf("  Width: %u\n", tex->texture[i].width);
        printf("  Height: %u\n", tex->texture[i].height);
        printf("  Bytes per Pixel: %u\n", tex->texture[i].bytes_per_pixel);
        printf("  Pixel Data Address: %p\n", (void*)tex->texture[i].pixels);
    }

    // Eğer xpm bilgileri varsa onları yazdır
    for (int i = 0; i < 4; i++) {
        if (tex->xpm[i]) {
            printf("XPM %d: Description or relevant info here\n", i);
            // Burada xpm yapısının içeriklerine göre detaylı bilgileri yazdırabilirsiniz
        }
    }

    printf("Texture Side: %d\n", tex->side);
}

void print_parsed_data(const t_cube_data *data) {
    if (!data || !data->res) {
        printf("No data to display.\n");
        return;
    }

    printf("Parsed Data from file '%s':\n", data->source_file);
    printf("Map Width, Type: uint32_t, Value: %zu\n", data->res->map_width);
    printf("Map Height, Type: uint32_t, Value: %zu\n", data->res->map_height);

    // Texture verilerini yazdır
    print_texture_details(&data->texture);
}




void	free_cubed(t_cube_data *cubed);
void	key_hooks(t_cube_data *data);
int		paint_background(t_cube_data *game);
uint8_t	parse_file(t_cube_data *data, const char *path_to_file);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <path_to_cub_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	t_cube_data cubed;
	cubed.source_file = argv[1];  // Girdi olarak verilen dosya adını kaydet

	if (parse_file(&cubed, argv[1]) != 0) {
		fprintf(stderr, "Failed to parse the .cub file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	// Parse edilen verileri yazdır
	print_parsed_data(&cubed);

	return EXIT_SUCCESS;  // Program başarılı bir şekilde tamamlandı
}
