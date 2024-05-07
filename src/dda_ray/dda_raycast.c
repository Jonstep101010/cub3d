#include "cube.h"

t_dda perform_dda(t_cube *game, t_player *player, t_ray *ray)
{
	t_dda dda;
	initialize_dda(&dda, player);
	calculate_delta(ray, player);
	set_initial_step(&dda, ray, player);

	while (true)
	{
		perform_dda_step(&dda, ray);
		while (game->game_map.map_height > dda.map_y && game->game_map.map_width > dda.map_x)
		{
			if (dda.x < dda.y)
			{
				dda.x += game->ray.delta_x;
				dda.map_x += dda.step_x;
				if (game->ray.dir_x > 0)
					game->texture.side = EAST;
				else
					game->texture.side = WEST;
			} else
			{
				dda.y += game->ray.delta_y;
				dda.map_y += dda.step_y;
				if (game->ray.dir_y > 0)
					game->texture.side = SOUTH;
				else
					game->texture.side = NORTH;
			}
			// Check if the ray has hit a wall
			if (!(game->game_map.map_height > dda.map_y || game->game_map.map_width > dda.map_x)
				&& game->game_map.map[dda.map_y][dda.map_x] == '1')
			{
				printf("Wall hit at map_x=%d, map_y=%d\n", dda.map_x, dda.map_y);
				break;  // Wall found
			}
		}
	}
	return (dda);
}

int	pixell(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_wall_section(t_cube *game, t_draw *draw, int col)
{
	unsigned int color;
	int t = draw->start - 1; // Start from the beginning of the wall section
	uint8_t *pixel;
	int num;

	// Loop over each pixel in the wall section vertically
	while (++t <= draw->end)
	{
		if (draw->texture_y < game->texture.texture[game->texture.side].height)
		{
			num = game->texture.texture[game->texture.side].width * 4 * (int)draw->texture_y + (int)draw->texture_x * 4;
			pixel = &game->texture.texture[game->texture.side].pixels[num];
			color = pixell(pixel[0], pixel[1], pixel[2], pixel[3]);
			mlx_put_pixel(game->image, col, t, color);
			draw->texture_y += draw->text_step;
		}
	}
}

void draw_ceiling_and_floor(t_cube *game, t_draw *draw, int col)
{
	int t = -1;
	while (++t < SCREEN_HEIGHT)
	{
		if (t < draw->start)
		{
			mlx_put_pixel(game->image, col, t, pixell(game->ceil_c.r, game->ceil_c.g, game->ceil_c.b, 255));
		}
		else if (t > draw->end)
		{
			mlx_put_pixel(game->image, col, t, pixell(game->floor_c.r, game->floor_c.g, game->floor_c.b, 255));
		}
	}
}

void	draw_texture(t_cube *game, int col, double perp_wall_dist)
{
	t_draw	draw;

	draw.height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		// Calculate the starting and ending y-coordinates for the line on the screen.
	// This centers the line vertically based on its calculated height.
	draw.start =(SCREEN_HEIGHT / 2) - (draw.height / 2);     // Çizimin başlayacağı y noktası
	draw.end = draw.height / 2 + (SCREEN_HEIGHT / 2);

	if((game->texture.side) == EAST || (game->texture.side) == WEST)
		draw.wall_x = game->player.y + perp_wall_dist * game->ray.dir_y;
	else
		draw.wall_x = game->player.x + perp_wall_dist * game->ray.dir_x;

	 // Use only the fractional part of the wall x-coordinate by subtracting its floor value.
	// This is essential for correct texture wrapping and alignment on the wall.
	draw.wall_x -= floor(draw.wall_x);

// Calculate the exact horizontal position within the texture from which to sample pixels
		draw.texture_x = (int)(draw.wall_x * \
	(double)game->texture.texture[game->texture.side].width);

	// Initialize the texture sampling position along the y-axis of the texture
	draw.texture_y = 0; // Starts sampling from the top of the texture

	// Calculate the rate at which to move down the texture's y-axis per screen pixel drawn
	draw.text_step = (double)game->texture.texture[game->texture.side].height / (double)draw.height;  // Adjust texture sampling rate based on line height

	// Adjust the texture sampling start position if the top of the wall slice is off-screen
	if(draw.start < 0)  // If the starting point is above the screen
		draw.texture_y = fabs((double)draw.start) * draw.text_step;  //adjust text_y to skip the unseen part of the texture

	draw_ceiling_and_floor(game, &draw, col); // Draw ceiling and floor
	draw_wall_section(game, &draw, col); // Draw the wall section
}

void initialize_dda(t_dda *dda, t_player *player)
{
	// printf("Initializing DDA...\n");
	dda->map_x = (int)(player->x);
	dda->map_y = (int)(player->y);
	// printf("Initial map position: map_x=%d, map_y=%d\n", dda->map_x, dda->map_y);
}

void calculate_delta(t_ray *ray, t_player *player)
{
	// printf("Calculating delta values...\n");
	if (player->dir_x == 0) {
		ray->delta_x = 1e30;
	} else {
		ray->delta_x = fabs(1 / player->dir_x);
	}
	if (player->dir_y == 0) {
		ray->delta_y = 1e30;
	} else {
		ray->delta_y = fabs(1 / player->dir_y);
	}
	// printf("Delta values: delta_x=%f, delta_y=%f\n", ray->delta_x, ray->delta_y);
}

void set_initial_step(t_dda *dda, t_ray *ray, t_player *player)
{
	// printf("Setting initial steps...\n");
	double rayPosX = player->x;
	double rayPosY = player->y;

	if (player->dir_x < 0) {
		dda->step_x = -1;
		dda->x = (rayPosX - dda->map_x) * ray->delta_x;
	} else {
		dda->step_x = 1;
		dda->x = (dda->map_x + 1.0 - rayPosX) * ray->delta_x;
	}

	if (player->dir_y < 0) {
		dda->step_y = -1;
		dda->y = (rayPosY - dda->map_y) * ray->delta_y;
	} else {
		dda->step_y = 1;
		dda->y = (dda->map_y + 1.0 - rayPosY) * ray->delta_y;
	}

	// printf("Steps: step_x=%d, x=%f, step_y=%d, y=%f\n", dda->step_x, dda->x, dda->step_y, dda->y);
}

void perform_dda_step(t_dda *dda, t_ray *ray)
{
	// printf("Performing DDA step...\n");
	if (dda->x < dda->y) {
		dda->x += ray->delta_x;
		dda->map_x += dda->step_x;
	} else {
		dda->y += ray->delta_y;
		dda->map_y += dda->step_y;
	}
	// printf("DDA step results: x=%f, map_x=%d, y=%f, map_y=%d\n", dda->x, dda->map_x, dda->y, dda->map_y);
}

void draw_map(t_cube *game)
{
	// printf("Drawing map...\n");
	int i = -1;
	while(++i < SCREEN_WIDTH)
	{
		double camera_x = 2 * i / (double)SCREEN_WIDTH - 1; //normalize the screen x coord
		game->ray.dir_x = game->player.dir_x + game->plane_x * camera_x;
		game->ray.dir_y = game->player.dir_y + game->plane_y * camera_x;
		calculate_delta(&game->ray, &game->player);
		// printf("Ray direction for column %d: dir_x=%f, dir_y=%f\n", i, game->ray.dir_x, game->ray.dir_y);

		t_dda calc_distance = perform_dda(game, &game->player, &game->ray);
		if(game->texture.side == EAST || game->texture.side == WEST)
			draw_texture(game, i, calc_distance.x - game->ray.delta_x);
		else
			draw_texture(game, i, calc_distance.y - game->ray.delta_y);
	}
}
