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
	TEST_ASSERT(0 == returns_one());
}
