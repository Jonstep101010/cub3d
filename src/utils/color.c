#include "structs.h"
#include <stdint.h>

uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b)
{
	return (((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b);
}

t_rgb	create_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	t_rgb	color;

	color = (t_rgb) {
		.r = r,
		.g = g,
		.b = b,
	};
	return (color);
}

t_rgb	create_rgb_hex(uint32_t hex)
{
	t_rgb	color;

	color = (t_rgb) {
		.r = (hex >> 16) & 0xFF,
		.g = (hex >> 8) & 0xFF,
		.b = hex & 0xFF,
	};
	return (color);
}
