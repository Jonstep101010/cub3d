#include "input.h"
#include "libft.h"

static	char	**get_tex_member(t_cube_textures *files, int direction)
{
	if (direction == 0)
		return (&files->path_north);
	if (direction == 1)
		return (&files->path_east);
	if (direction == 2)
		return (&files->path_south);
	if (direction == 3)
		return (&files->path_west);
	return (NULL);
}

// handle alloc fail/free mem
static	uint8_t	tex_direction(const char *line, t_cube_textures *files, int direction)
{
	char	**path;

	path	= get_tex_member(files, direction);
	if (*path)
		return (1);
	*path = ft_strtrim(line + 2, " ");
	if (!*path)
		return (1);
	// set flag
	if (files->path_north && files->path_east
		&& files->path_south && files->path_west)
		files->set = true;
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
	while (i < 4)
	{
		if (ft_strncmp(line, directions[i], 2) == 0)
		{
			return (tex_direction(line, files, i) != 0);
		}
		i++;
	}
	return (1);
}
