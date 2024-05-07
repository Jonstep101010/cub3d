#ifndef UTILS_H
# define UTILS_H

#include "structs.h"
#include <stdint.h>
uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b);
t_rgb		create_rgb(uint8_t r, uint8_t g, uint8_t b);
t_rgb		create_rgb_hex(uint32_t hex);

#endif