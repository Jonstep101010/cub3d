#include "cubed.h"
#include "input.h"
#include "struct.h"
#include <stdlib.h>
#include <string.h>

uint8_t	check_file(const char *path_to_file)
{
	(void)path_to_file;
	// check filename...
	return (0);
}

#include "libutils.h"
#include "libft.h"
#include <fcntl.h>
uint8_t	parse_file(t_cube_data *data, const char *path_to_file)
{
	const size_t	len = secure_strlen(path_to_file);
	int fd;


	// check file extension
	if (len < 5 || ft_strncmp(".cub", &path_to_file[len - 4], 4))
		printf("error\n"), exit(1);
	fd = open(path_to_file, O_RDONLY);
	if (fd == -1)
		printf("error\n"), exit(1);

	// create cube_file struct
	t_cube_file	*cubefile;

	cubefile = ft_calloc(1, sizeof(*cubefile));
	if (!cubefile)
		return (close(fd), EXIT_FAILURE);
	data->file = cubefile;
	data->file->fd = fd;

	// open file & check fd

	// check contents & set values

	// validate map

	return (0);
}
