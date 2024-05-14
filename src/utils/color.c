#include "structs.h"
#include <stdint.h>

uint32_t	rgb_to_hex(uint8_t rgb[3])
{
	return (
		((uint32_t)rgb[0] << 16)
		| ((uint32_t)rgb[1] << 8)
		| (uint32_t)rgb[2]
	);
}

t_rgb	create_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return ((t_rgb){
		.r = r,
		.g = g,
		.b = b,
	});
}

t_rgb	create_rgb_hex(uint32_t hex)
{
	return ((t_rgb){
		.r = (hex >> 16) & 0xFF,
		.g = (hex >> 8) & 0xFF,
		.b = hex & 0xFF,
	});
}
