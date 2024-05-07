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
	if (ray->dirX == 0)
	{
		ray->deltaDistX = 1e10;
		perror("Warning: Ray direction X is zero, adjusted calculation to avoid division by zero.");
	}
	else
	{
		ray->deltaDistX = fabs(1 / ray->dirX);
	}
	if (ray->dirY == 0)
	{
		ray->deltaDistY = 1e10;
		perror("Warning: Ray direction Y is zero, adjusted calculation to avoid division by zero.");
	}
	else
	{
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




void draw_map(t_cube *game)
{
	int		i;
	double	camera_x,
	t_dda	calc_distance;

	i = -1;
	while(++x < SCREEN_WIDTH)
	{
		camera_x = 2 * i / (double)SCREEN_WIDTH - 1;
		game->ray.x = game->player.dir_x + game->plane_x * camera_x;
		game->ray.y = game->player.dir_y + game->plane_y * camera_x;
		if(game->ray.x == 0)
			game->ray.delta.x = 1e30;
		else
			game->ray.delta_x = fabs(1 / game->ray.x);
		if (game->ray.y == 0)
			game->ray.delta_y = 1e30;
		else
			game->ray.delta_y = fabs(1 / game->ray.y);

		calc_distance = perform_dda(game);
		if(game->textures.side_text == NORTH || game->textures.side_text == SOUTH)
			draw_texture(game, i, calc_distance.x - game->ray.delta_x)
		else
			draw_texture(game, i, calc_distance.y - game->ray.delta_y)
	}

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
