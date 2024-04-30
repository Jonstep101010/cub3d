#include "cube.h"

void initialize_dda(t_dda *dda, t_player *player)
{
	dda->map_x = (int)(player->x);
	dda->map_y = (int)(player->y);
}

void calculate_delta(t_ray *ray, t_player *player)
{
	if (player->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / player->dir_x);
	if (player->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / player->dir_y);
}

void set_initial_step(t_dda *dda, t_ray *ray, t_player *player)
{
	double rayPosX = player->x;
	double rayPosY = player->y;
	if (player->dir_x < 0)
	{
		dda->step_x = -1;
		dda->x = (rayPosX - dda->map_x) * ray->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->x = (dda->map_x + 1.0 - rayPosX) * ray->delta_x;
	}
	if (player->dir_y < 0)
	{
		dda->step_y = -1;
		dda->y = (rayPosY - dda->map_y) * ray->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->y = (dda->map_y + 1.0 - rayPosY) * ray->delta_y;
	}
}

void perform_dda_step(t_dda *dda, t_ray *ray)
{
	if (dda->x < dda->y)
	{
		dda->x += ray->delta_x;
		dda->map_x += dda->step_x;
	}
	else
	{
		dda->y += ray->delta_y;
		dda->map_y += dda->step_y;
	}
}

t_dda perform_dda(t_game *game, t_player *player, t_ray *ray)
{
	t_dda dda;
	initialize_dda(&dda, player);
	calculate_delta(ray, player);
	set_initial_step(&dda, ray, player);

	while (true)
	{
		perform_dda_step(&dda, ray);
		if (check_wall_hit(game, dda.map_x, dda.map_y))
			break;
	}
	return (dda);
}



int check_wall_hit(t_game *game, t_dda *dda)
{
	while (true)
	{
		if (dda->x < dda->y)
		{
			dda->x += game->ray.delta_x;
			dda->map_x += dda->step_x;
			if (game->ray.dir_x > 0)
				game->wall.side = EAST;
			else
				game->wall.side = WEST;
		} else
		{
			dda->y += game->ray.delta_y;
			dda->map_y += dda->step_y;
			if (game->ray.dir_y > 0)
				game->wall.side = SOUTH;
			 else
				game->wall.side = NORTH;
		}
		// Check if the ray has hit a wall
		if (game->map[dda->map_y][dda->map_x] == 1)
			return (1);  // Wall found
	}
	return (0);
}



void draw_map(t_game *game)
{
	int i;
	double cameraX;
	t_ray ray;
	t_dda dda;

	for (i = 0; i < SCREEN_WIDTH; i++) {
		// Kamera düzlemindeki x pozisyonunu hesapla
		cameraX = 2 * i / (double)SCREEN_WIDTH - 1;  // Normalizasyon ve merkezden kaydırma

		// Ray'ın yön vektörlerini hesapla
		ray.x = game->player.dir_x + game->plane_x * cameraX;
		ray.y = game->player.dir_y + game->plane_y * cameraX;

		// Ray için delta değerlerini hesapla
		calculate_delta(&ray, &game->player);

		// DDA algoritmasını çalıştır ve çarpma bilgisini al
		dda = perform_dda(game, &game->player, &ray);

		// Eğer doğu veya batı duvarına çarpıldıysa
		if (game->wall.side == EAST || game->wall.side == WEST) {
			// Duvarın mesafesine göre texture çiz (x delta değerine bağlı olarak ayarla)
			draw_texture(game, i, dda.x - ray.delta_x);
		} else {
			// Duvarın mesafesine göre texture çiz (y delta değerine bağlı olarak ayarla)
			draw_texture(game, i, dda.y - ray.delta_y);
		}
	}
}



void	draw_texture(t_game *game, int x, double perp_wall_dist)
{
	t_draw	draw;
	draw.height = (int)(SCREEN_HEIGHT / perp_wall_dist);  // Duvarın ekran üzerindeki yüksekliği
	draw.start =(-height / 2) + (SCREEN_HEIGHT / 2);     // Çizimin başlayacağı y noktası

	if (draw.start < 0)
		draw.start = 0;
	draw.end = draw.height / 2 + SCREEN_HEIGHT / 2;       // Çizimin biteceği y noktası
	if (draw.end >= SCREEN_HEIGHT)
		draw.end = SCREEN_HEIGHT - 1;

	// Texture bilgilerini al
	t_texture *texture = &game->textures[game->wall.side];  // Texture, duvarın yönüne bağlı olarak seçilir
	int texWidth = texture->texture.width;                 // Texture genişliği
	int texHeight = texture->texture.height;               // Texture yüksekliği

	// Texture'dan hangi x koordinatının çizileceğini hesapla
	double wallX = game->player.x + perp_wall_dist * game->ray.dir_x;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)(texWidth));
	if (game->wall.side == EAST || game->wall.side == WEST) {
		texX = texWidth - texX - 1;  // Duvar yüzeyi yönüne bağlı olarak texture x koordinatını ayarla
	}

	// Sütunu texture olarak çiz
	for (int y = drawStart; y < drawEnd; y++) {
		int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;  // 256 ve 128, texture çiziminde kullanılan sabitler
		int texY = ((d * texHeight) / lineHeight) / 256;
		uint32_t color = texture->texture.data[texWidth * texY + texX];  // Texture'dan renk bilgisini al
		draw_pixel(game, x, y, color);  // Pixeli çiz
	}
}
