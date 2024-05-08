#include "cube.h"
#include <math.h>
#include <stdlib.h>
#include "input.h"
#include "libft.h"

void init_player_start_position(t_cube *game)
{
	game->player.x = game->res->p_start.x;
	game->player.y = game->res->p_start.y;
	game->player.starting_posx = (double)game->res->p_start.x + 0.5;
	game->player.starting_posy = (double)game->res->p_start.y + 0.5;
}

////// INIT PLAYER DIRECTION////

void	init_player_direction_ns(t_cube *game)
{
	game->player.dir_x = 0.0;
	game->plane_y = 0.0;
	if (game->res->p_start.dir_nsew == 'N')
	{
		game->player.dir_y = -1.0;
		game->plane_x = 0.66;
	}
	else if (game->res->p_start.dir_nsew == 'S')
	{
		game->player.dir_y = 1.0;
		game->plane_x = -0.66;
	}
}

void	init_player_direction_ew(t_cube *game)
{
	game->player.dir_y = 0.0;
	game->plane_x = 0.0;
	if (game->res->p_start.dir_nsew == EAST) {
		game->player.dir_x = 1.0;
		game->plane_y = 0.66;
	} else if (game->res->p_start.dir_nsew == WEST) {
		game->player.dir_x = -1.0;
		game->plane_y = -0.66;
	}
}

void init_player_direction(t_cube *game) {
	if (game->res->p_start.dir_nsew == EAST || game->res->p_start.dir_nsew == WEST)
		init_player_direction_ew(game);
	else if (game->res->p_start.dir_nsew == 'N' || game->res->p_start.dir_nsew == SOUTH)
		init_player_direction_ns(game);
	else {
		ft_putendl_fd(ERR_INVALID_DIR, 2);
		exit(EXIT_FAILURE);
	}
}


void print_game_info(t_cube *game)
{
	// Güvenlik önlemi olarak pointer'ın geçerli olduğundan emin olun
	if (!game || !game->res->map_lines) {
		// fprintf(stderr, "Game data is not initialized properly.\n");
		return;
	}

	// printf("Player Info:\n");

	// Oyuncu başlangıç pozisyonlarını yazdırırken 1 ekleyerek 1-indexed olarak göster
	// Ayrıca, floating-point değerlerin geçerli olduğunu kontrol edin
	if (isfinite(game->player.starting_posx) && isfinite(game->player.starting_posy)) {
		// printf(" Position: (%f, %f)\n", game->player.starting_posx, game->player.starting_posy );
	} else {
		// printf(" Position: Invalid\n");
	}

	// Yön bilgilerini kontrol ederek yazdırın
	if (isfinite(game->player.dir_x) && isfinite(game->player.dir_y)) {
		// printf(" Direction: %s (%f, %f)\n", get_direction_name(game->res->p_start.dir_nsew), game->player.dir_x, game->player.dir_y);
	} else {
		// printf(" Direction: Invalid\n");
	}

	// Kamera düzlemi bilgilerini kontrol ederek yazdırın
	if (isfinite(game->plane_x) && isfinite(game->plane_y)) {
		// printf(" Camera Plane: (%f, %f)\n", game->plane_x, game->plane_y);
	} else {
		// printf(" Camera Plane: Invalid\n");
	}

	// printf("\nGame Map:\n");

	for (size_t i = 0; i < game->res->map_height; i++) {
		if (game->res->map_lines[i].y_view) { // Satırın null olmadığından emin olun
			// printf(" %s\n", game->res->map_lines[i].y_view);
		} else {
			// printf(" Error: Map row is null\n");
		}
	}

	// printf("Map Dimensions: %d x %d\n", game->res->map_width, game->res->map_height);
}

// Global olarak tanımlanmış map
const char *GLOBAL_STATIC_MAP[] =
{
	"1111111111",
	"1000011111",
	"1000011111",
	"1100000001",
	"10000N0001",
	"1111111111"
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_map(t_cube *game)
{
	game->res = calloc(1, sizeof(t_parse_res));
	game->res->map_height = sizeof(GLOBAL_STATIC_MAP) / sizeof(GLOBAL_STATIC_MAP[0]);
	size_t i = 0;

	while (i < game->res->map_height)
	{
		size_t current_length = strlen(GLOBAL_STATIC_MAP[i]);
		if (current_length > game->res->map_width)
		{
			game->res->map_width = current_length;
		}
		i++;
	}
	// @audit align behaviour with build_map_lines
	game->res->map_lines = calloc(game->res->map_height + 1, sizeof(t_map_line));
	if (!game->res->map_lines)
	{
		// // fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < game->res->map_height)
	{
		game->res->map_lines[i].y_view = calloc(game->res->map_width + 1, sizeof(char));
		game->res->map_lines[i].y_view =  ft_strdup(GLOBAL_STATIC_MAP[i]);
		i++;
	}
	game->floor_c = (t_rgb){255, 100, 50};  // floor için organge
	game->ceil_c = (t_rgb){100, 100, 255}; // ceiling için blue
}

bool	parse_player_data(t_map_line *map_lines, t_parse_player *player);

void	mock_dda(void)
{
	t_cube game; // Initialize the game structure
	load_map(&game); // Load the map into the game structure
	if (!parse_player_data(game.res->map_lines, &game.res->p_start))
		fprintf(stderr, "MOCK: player position not found\n"), exit(1);
	init_player_direction(&game); // Initialize player direction based on start position
	draw_map(&game);
	print_game_info(&game); // Print game info to check all is loaded correctly
}
