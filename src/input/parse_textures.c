#include "input.h"
#include "libft.h"

static	uint8_t	tex_direction(const char *line, t_cube_textures *files, int direction)
{
	char	*paths[4] = {files->path_north, files->path_east, files->path_south, files->path_west};
	if (paths[direction])
		return (1);
	paths[direction] = ft_strtrim(line + 2, " ");
	if (!paths[direction])
		return (1);
	const char	directions[4][2] = {"NO", "EA", "SO", "WE"};
	printf("path: %s: %s\n", directions[direction], paths[direction]);
	return (0);
}

int	check_textures(const char *line, t_cube_textures *files)
{
	int			i;
	const char	directions[4][2] = {"NO", "EA", "SO", "WE"};

	i = 0;
	if (files->path_north && files->path_east
		&& files->path_south && files->path_west)
		return (1);
	// handle incorrect letters
	while (i < 4)
	{
		if (ft_strncmp(line, directions[i], 2))
		{
			if (tex_direction(line, files, i) != 0)
				return (1);
			// set flag
			if (files->path_north && files->path_east
				&& files->path_south && files->path_west)
				files->set = true;
		}
		i++;
	}
	return (0);
}
