#include "cube.h"
#include "utils.h"
#include "defines.h"
#include <math.h>
#include <stdio.h>
#include "input.h"
#include "struct.h"


void draw_column(mlx_image_t *img, t_draw *draw, int col, mlx_texture_t *texture, uint32_t ceiling_color, uint32_t floor_color)
{
	int y = 0;
	int tex_y;
	uint32_t color;
	uint8_t *pixels = texture->pixels;
	const int img_height = (int)img->height;
	const int img_width = (int)img->width;
	const int tex_width = texture->width;
	const int tex_height = texture->height;
	while (y < draw->start)
	{
		if (y >= 0 && y < img_height && col >= 0 && col < img_width)
			mlx_put_pixel(img, col, y, ceiling_color);
		y++;
	}
	double current_texture_y = draw->texture_y;
	while (y < draw->end)
	{
		tex_y = (int)current_texture_y & (tex_height - 1);
		current_texture_y += draw->text_step;
		int tex_index = (tex_y * tex_width + draw->texture_x) * 4;
		uint8_t r = pixels[tex_index];
		uint8_t g = pixels[tex_index + 1];
		uint8_t b = pixels[tex_index + 2];
		uint8_t a = pixels[tex_index + 3];
		color = (r << 24) | (g << 16) | (b << 8) | a;
		if (y >= 0 && y < img_height && col >= 0 && col < img_width)
			mlx_put_pixel(img, col, y, color);
		y++;
	}
	while (y < img_height)
	{
		if (y >= 0 && y < img_height && col >= 0 && col < img_width)
			mlx_put_pixel(img, col, y, floor_color);
		y++;
	}
}

void calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw)
{
	if (game->texture_side == W || game->texture_side == E)
		draw->wall_x = game->player.y + wall_distance * game->ray.dir_y;
	else
		draw->wall_x = game->player.x + wall_distance * game->ray.dir_x;
	draw->wall_x -= floor(draw->wall_x);
}

void calculate_texture_coordinates(t_cube_data *game, t_draw *draw)
{
	draw->texture_x = (int)(draw->wall_x * (double)game->res->tex[game->texture_side]->width);
	draw->texture_y = 0;
	draw->text_step = (double)game->res->tex[game->texture_side]->height / draw->height;
	if (draw->start < 0)
		draw->texture_y = -draw->start * draw->text_step;
}

void draw_line_of_texture(t_cube_data *game, int col, double wall_distance)
{
	if (game == NULL || game->res == NULL || game->res->tex[game->texture_side] == NULL)
	{
		perror("Invalid game or resource data");
		return;
	}
	t_draw draw;
	draw.height = (int)(HEIGHT / wall_distance);
	draw.start = SCREEN_MIDDLE - HALF_HEIGHT(draw.height);
	draw.end = draw.start + draw.height;
	if (game->texture_side == W || game->texture_side == E)
		draw.wall_x = game->player.y + wall_distance * game->ray.dir_y;
	else
		draw.wall_x = game->player.x + wall_distance * game->ray.dir_x;
	draw.wall_x -= floor(draw.wall_x);
	draw.texture_x = (int)(draw.wall_x * (double)game->res->tex[game->texture_side]->width);
	draw.texture_y = 0;
	draw.text_step = (double)game->res->tex[game->texture_side]->height / draw.height;
	if (draw.start < 0)
	{
		draw.texture_y = -draw.start * draw.text_step;
		draw.start = 0;
	}
	if (draw.end >= HEIGHT)
		draw.end = HEIGHT - 1;
	draw_column(game->image, &draw, col, game->res->tex[game->texture_side], game->res->ceiling, game->res->floor);
}

void draw_map(t_cube_data *cubed)
{
	uint32_t *pixels = (uint32_t *)cubed->image->pixels;
	int total_pixels = WIDTH * HEIGHT;
	for (int i = 0; i < total_pixels; i++) {
		pixels[i] = 0x000000FF; // Clear the image with a black color
	}

	t_dda dist;
	double cam_x;
	int i;

	for (i = 0; i < WIDTH; ++i)
	{
		cam_x = 2 * i / (double)WIDTH - 1;
		cubed->ray.dir_x = cubed->player.dir_x + cubed->player.plane_x * cam_x;
		cubed->ray.dir_y = cubed->player.dir_y + cubed->player.plane_y * cam_x;
		cubed->ray.delta_x = (cubed->ray.dir_x == 0) ? INFINITY : fabs(1 / cubed->ray.dir_x);
		cubed->ray.delta_y = (cubed->ray.dir_y == 0) ? INFINITY : fabs(1 / cubed->ray.dir_y);
		dist = dda(cubed);
		double wall_distance = (cubed->texture_side == E || cubed->texture_side == W)
			? dist.x - cubed->ray.delta_x
			: dist.y - cubed->ray.delta_y;
		draw_line_of_texture(cubed, i, wall_distance);
	}
}
