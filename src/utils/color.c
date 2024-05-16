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

uint32_t	rgb_arr_hex(int rgb[3])
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}
