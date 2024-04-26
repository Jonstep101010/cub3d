#include "input.h"
#include "libft.h"
#include "libutils.h"
#include <fcntl.h>

static char	**get_tex_member(t_cube_textures *files, int direction)
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

/**
 * @brief make sure there are texfiles for each direction
 */
static uint8_t	check_paths_differ(char **path,
	t_cube_textures *files, int direction)
{
	char			**other_paths;
	int				i;
	const size_t	len = ft_strlen(*path);

	i = 0;
	while (i < 4)
	{
		if (i != direction)
		{
			other_paths = get_tex_member(files, i);
			if (other_paths && len == secure_strlen(*other_paths)
				&& ft_strnstr(*path, *other_paths, len))
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief check that texfile exists, no conflicts with existing
 */
static	uint8_t	tex_direction(const char *line,
	t_cube_textures *files, int direction)
{
	char	**path;
	int		fd;

	path = get_tex_member(files, direction);
	if (*path)
		return (1);
	*path = ft_strtrim(line + 2, " ");
	if (!*path || !**path)
		return (1);
	if (check_paths_differ(path, files, direction) != 0)
		return (1);
	fd = open(*path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	if (files->path_north && files->path_east
		&& files->path_south && files->path_west)
		files->set = true;
	return (0);
}

/**
 * @brief check if the line is a texture line, dispatch parsing
 */
int	check_textures(const char *line, t_cube_textures *files)
{
	int			i;
	const char	directions[4][2] = {"NO", "EA", "SO", "WE"};

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(line, directions[i], 2) == 0)
		{
			// @follow-up enable error printing, handle free mem
			return (tex_direction(line, files, i) != 0);
		}
		i++;
	}
	return (1);
}
