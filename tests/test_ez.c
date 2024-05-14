#include "unity.h"

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}

int returns_one() {
	return 1;
}

#include <stdio.h>
void	test_ez() {
	TEST_ASSERT(1 == returns_one());
}

#include "structs.h"
#include "utils.h"

void	test_rgb_color() {
	t_rgb	color;
	color = create_rgb(255, 127, 127);
	TEST_ASSERT(color.r == 255);
	TEST_ASSERT(color.g == 127);
	TEST_ASSERT(color.b == 127);
}

void	test_rgb_hex_color() {
	t_rgb	color;
	uint32_t	hex = 0xFF7F7F;
	color = create_rgb_hex(hex);
	TEST_ASSERT(color.r == 255);
	TEST_ASSERT(color.g == 127);
	TEST_ASSERT(color.b == 127);
}

void	test_rgb_hex_color_equal() {
	const uint32_t	hex = rgb_to_hex((uint8_t[3]){255, 127, 127});
	TEST_ASSERT_EQUAL_UINT32(0xFF7F7F, hex);
	t_rgb	color;
	color = create_rgb_hex(hex);
	TEST_ASSERT(color.r == 255);
	TEST_ASSERT(color.g == 127);
	TEST_ASSERT(color.b == 127);
}
