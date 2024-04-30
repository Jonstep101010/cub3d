#include "cube.h"

#include "cube.h"


void set_initial_ray_direction(t_player *player, t_ray *ray, double cameraX)
{
    ray->originX = player->posX;
    ray->originY = player->posY;
    ray->dirX = player->dir_x + player->plane_x * cameraX;
    ray->dirY = player->dir_y + player->plane_y * cameraX;
}

void calculate_delta_distances(t_ray *ray)
{
    if (ray->dirX == 0) {
        ray->deltaDistX = 1e10;
        perror("Warning: Ray direction X is zero, adjusted calculation to avoid division by zero.");
    } else {
        ray->deltaDistX = fabs(1 / ray->dirX);
    }
    if (ray->dirY == 0) {
        ray->deltaDistY = 1e10;
        perror("Warning: Ray direction Y is zero, adjusted calculation to avoid division by zero.");
    } else {
        ray->deltaDistY = fabs(1 / ray->dirY);
    }
}


void set_ray_steps_and_side_distances(t_ray *ray)
{
    ray->mapX = (int)ray->originX;
    ray->mapY = (int)ray->originY;

    // Ray steps setting
    if (ray->dirX < 0)
        ray->stepX = -1;
	else
        ray->stepX = 1;
    if (ray->dirY < 0)
        ray->stepY = -1;
     else
        ray->stepY = 1;
    // Side distances calculation
    if (ray->dirX < 0)
        ray->sideDistX = (ray->originX - ray-> mapX) * ray-> deltaDistX;
	else
        ray->sideDistX = (ray->mapX + 1.0 - ray-> originX) * ray-> deltaDistX;
    if (ray->dirY < 0)
        ray->sideDistY = (ray->originY - ray-> mapY) * ray-> deltaDistY;
     else
        ray->sideDistY = (ray->mapY + 1.0 - ray-> originY) * ray-> deltaDistY;

}

void initialize_ray(t_player *player, t_ray *ray, double cameraX)
{
	set_initial_ray_direction(player, ray, cameraX);
	calculate_delta_distances(ray);
	set_ray_steps_and_side_distances(ray);
}


void perform_dda(t_cube *game, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit) {
		if (ray->sideDistX < ray->sideDistY) {
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = (ray->dirX < 0) ? WEST : EAST;
		} else {
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = (ray->dirY < 0) ? NORTH : SOUTH;
		}
		if (game->game_map.map[ray->mapX][ray->mapY] > 0) {
			ray->hit = 1;
		}
	}
}




void draw_map(t_cube *game) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        initialize_ray(&game->player, &game->rays[x], cameraX);
        perform_dda(game, &game->rays[x]);

        double wallDist = (game->rays[x].side == EAST || game->rays[x].side == WEST) ?
            (game->rays[x].mapX - game->player.posX + (1 - game->rays[x].stepX) / 2) / game->rays[x].dirX :
            (game->rays[x].mapY - game->player.posY + (1 - game->rays[x].stepY) / 2) / game->rays[x].dirY;

        draw_lineof_texture(game, x, wallDist, game->rays[x].side);
    }
}


void wall_hit(t_cube *game, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			if (ray->dirX > 0)			// Doğu veya Batı duvarı belirleniyor
				game->textures[ray->mapX][ray->mapY].direction = EAST; // Doğu duvarı
			else
				game->textures[ray->mapX][ray->mapY].direction = WEST; // Batı duvarı
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			// Güney veya Kuzey duvarı belirleniyor
			if (ray->dirY > 0)
				game->textures[ray->mapX][ray->mapY].direction = SOUTH; // Güney duvarı
			else
				game->textures[ray->mapX][ray->mapY].direction = NORTH; // Kuzey duvarı
		}
		// Harita üzerindeki değer duvarı temsil ediyorsa
		if (game->game_map.map[ray->mapX][ray->mapY] > 0)
			ray->hit = 1; // Duvara çarpma durumu, döngüden çık
	}
}
