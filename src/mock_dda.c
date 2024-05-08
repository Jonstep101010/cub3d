#include "cube.h"
#include <math.h>
#include <stdlib.h>
#include "libft.h"

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

///FIND THE PLAYER POSITION ////////////

t_direction determine_direction(char player_char) {
	if (player_char == 'N')
		return NORTH;
	else if (player_char == 'S')
		return SOUTH;
	else if (player_char == 'E')
		return EAST;
	else if (player_char == 'W')
		return WEST;
	else
		return NON;  // Tanımsız veya bilinmeyen yön
}

void init_player_start_position(t_cube *game, int x, int y, char player_char)
{
	game->player.x = x;
	game->player.y = y;
	game->player.starting_posx = (double)x + 0.5;
	game->player.starting_posy = (double)y + 0.5;
	game->player.player_start_dir = determine_direction(player_char);  // Burada düzeltildi
	// printf("Player initialized at position: (%f, %f) facing %s\n",
	// 	   game->player.starting_posx, game->player.starting_posy, get_direction_name(game->player.player_start_dir));  // Burada düzeltildi
}

// 'player_char' kullanımı
void find_player_start_position(t_cube *game)
{
	int y = 0;
	int x = 0;;
	bool found = false;

	while (y < game->game_map.map_height && !found)
	{
		x = 0;
		while (x < game->game_map.map_width && !found)
		{
			char current_char = game->game_map.map[y][x];
			if (is_player_char(current_char))
			{
				init_player_start_position(game, x, y, current_char);
				found = true;
			}
			x++;
		}
		y++;
	}
	if (!found) {
		ft_putendl_fd(ERR_NO_START_POS, 2);
		exit(EXIT_FAILURE);
	}
}

////// INIT PLAYER DIRECTION////

void	init_player_direction_ns(t_cube *game)
{
	game->player.dir_x = 0.0;
	game->plane_y = 0.0;
	if (game->player.player_start_dir == NORTH)
	{
		game->player.dir_y = -1.0;
		game->plane_x = 0.66;
	}
	else if (game->player.player_start_dir == SOUTH)
	{
		game->player.dir_y = 1.0;
		game->plane_x = -0.66;
	}
}

void	init_player_direction_ew(t_cube *game)
{
	game->player.dir_y = 0.0;
	game->plane_x = 0.0;
	if (game->player.player_start_dir == EAST) {
		game->player.dir_x = 1.0;
		game->plane_y = 0.66;
	} else if (game->player.player_start_dir == WEST) {
		game->player.dir_x = -1.0;
		game->plane_y = -0.66;
	}
}

// Oyuncunun yönünü başlatma
void init_player_direction(t_cube *game) {
	if (game->player.player_start_dir == EAST || game->player.player_start_dir == WEST)
		init_player_direction_ew(game);
	else if (game->player.player_start_dir == NORTH || game->player.player_start_dir == SOUTH)
		init_player_direction_ns(game);
	else {
		ft_putendl_fd(ERR_INVALID_DIR, 2);
		exit(EXIT_FAILURE);
	}
}

void initialize_game(t_cube *game) {
	find_player_start_position(game);
}

char* get_direction_name(t_direction dir) {
	if (dir == NORTH)
		return "North";
	else if (dir == SOUTH)
		return "South";
	else if (dir == EAST)
		return "East";
	else if (dir == WEST)
		return "West";
	else
		return "Unknown";
}

void print_game_info(t_cube *game)
{
	// Güvenlik önlemi olarak pointer'ın geçerli olduğundan emin olun
	if (!game || !game->game_map.map) {
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
		// printf(" Direction: %s (%f, %f)\n", get_direction_name(game->player.player_start_dir), game->player.dir_x, game->player.dir_y);
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

	// Oyun haritasını güvenli bir şekilde yazdırın
	for (int i = 0; i < game->game_map.map_height; i++) {
		if (game->game_map.map[i]) { // Satırın null olmadığından emin olun
			// printf(" %s\n", game->game_map.map[i]);
		} else {
			// printf(" Error: Map row is null\n");
		}
	}

	// printf("Map Dimensions: %d x %d\n", game->game_map.map_width, game->game_map.map_height);
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
	int num_rows = sizeof(GLOBAL_STATIC_MAP) / sizeof(GLOBAL_STATIC_MAP[0]);
	int num_cols = 0; // Her satır için maksimum sütun sayısını bul
	int i = 0;

	// Maksimum sütun sayısını hesaplama
	while (i < num_rows)
	{
		int current_length = strlen(GLOBAL_STATIC_MAP[i]);
		if (current_length > num_cols)
		{
			num_cols = current_length;
		}
		i++;
	}
	// Bellek ayırma
	game->game_map.map = calloc(num_rows + 1, sizeof(char *));
	if (game->game_map.map == NULL)
	{
		// // fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_rows)
	{
		game->game_map.map[i] = calloc((num_cols + 1), sizeof(char)); // +1 for null terminator
		if (game->game_map.map[i] == NULL)
		{
			// fprintf(stderr, "Memory allocation failed for row %d\n", i);
			exit(EXIT_FAILURE);
		}
		strcpy(game->game_map.map[i], GLOBAL_STATIC_MAP[i]);
		i++;
	}

	// Map boyutlarını ayarlama
	game->game_map.map_height = num_rows;
	game->game_map.map_width = num_cols;
	game->floor_c = (t_rgb){255, 100, 50};  // floor için organge
	game->ceil_c = (t_rgb){100, 100, 255}; // ceiling için blue

}

void	mock_dda(void)
{
	t_cube game; // Initialize the game structure
	load_map(&game); // Load the map into the game structure
	initialize_game(&game); // Initialize game settings, player start position, etc.
	init_player_direction(&game); // Initialize player direction based on start position
	draw_map(&game);
	print_game_info(&game); // Print game info to check all is loaded correctly
}
