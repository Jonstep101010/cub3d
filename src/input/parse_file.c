#include "cubed.h"
#include "input.h"
#include "struct.h"
#include <stdlib.h>

uint8_t	check_file(const char *path_to_file)
{
	// check filename...
	return (0);
}

uint8_t	parse_file(t_cube_data *data, const char *path_to_file)
{
	// create cube_file
	t_cube_file	*cubefile;

	cubefile = calloc(1, sizeof(*cubefile));
	if (!cubefile)
		return (EXIT_FAILURE);

	// check file extension

	// open file & check fd

	// check contents & set values

	// validate map

	return (0);
}
