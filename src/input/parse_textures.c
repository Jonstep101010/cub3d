#include "input.h"
#include "libft.h"
#include "libutils.h"
#include <fcntl.h>

static char	**get_tex_member(t_cube_textures *tex, int direction)
{
	if (direction == 0)
		return (&tex->path_north);
	if (direction == 1)
		return (&tex->path_east);
	if (direction == 2)
		return (&tex->path_south);
	if (direction == 3)
		return (&tex->path_west);
	return (NULL);
}

static	bool	load_textures(t_cube_textures *tex)
{
	mlx_texture_t	*textures[4];
	char			**path;
	int				i;

	i = -1;
	while (++i < 4)
	{
		path = get_tex_member(tex, i);
		if (!path)
			return (false);
		textures[i] = mlx_load_png(*path);
		free_null(path);
		if (!textures[i])
		{
			while (i-- > 0)
				mlx_delete_texture(textures[i]);
			return (false);
		}
	}
	tex->north = textures[0];
	tex->east = textures[1];
	tex->south = textures[2];
	tex->west = textures[3];
	return (true);
}

void	free_textures(t_cube_textures *tex)
{
	free_null(&tex->path_north);
	free_null(&tex->path_east);
	free_null(&tex->path_south);
	free_null(&tex->path_west);
	if (tex->set)
	{
		mlx_delete_texture(tex->north);
		mlx_delete_texture(tex->east);
		mlx_delete_texture(tex->south);
		mlx_delete_texture(tex->west);
	}
}

/**
 * @brief make sure there are textex for each direction
 */
static uint8_t	check_paths_differ(char **path,
	t_cube_textures *tex, int direction)
{
	char			**other_paths;
	int				i;
	const size_t	len = ft_strlen(*path);

	i = 0;
	while (i < 4)
	{
		if (i != direction)
		{
			other_paths = get_tex_member(tex, i);
			if (other_paths && len == secure_strlen(*other_paths)
				&& ft_strnstr(*path, *other_paths, len))
				return (1);
		}
		i++;
	}
	return (0);
}

static void free_texpaths(t_cube_textures *tex)
{
	free_null(tex->path_north);
	free_null(tex->path_east);
	free_null(tex->path_west);
	free_null(tex->path_south);
}

/**
 * @brief check that texfile exists, no conflicts with existing
 */
static	uint8_t	tex_direction(const char *line,
	t_cube_textures *tex, int direction)
{
	char	**path;
	int		fd;

	path = get_tex_member(tex, direction);
	if (*path)
		return (free_texpaths(tex), 1);
	*path = ft_strtrim(line + 2, " ");
	if (!*path || !**path)
		return (free_texpaths(tex), 1);
	if (check_paths_differ(path, tex, direction) != 0)
		return (free_texpaths(tex), 1);
	fd = open(*path, O_RDONLY);
	if (fd == -1)
		return (free_texpaths(tex), 1);
	close(fd);
	if (tex->path_north && tex->path_east
		&& tex->path_south && tex->path_west)
	{
		if (!load_textures(tex))
			return (1);
		tex->set = true;
	}
	return (0);
}

/**
 * @brief check if the line is a texture line, dispatch parsing
 */
int	check_textures(const char *line, t_cube_textures *tex)
{
	int			i;
	const char	directions[4][2] = {"NO", "EA", "SO", "WE"};

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(line, directions[i], 2) == 0)
		{
			// @follow-up enable error printing, handle free mem
			if (tex_direction(line, tex, i) != 0)
				return (free_textures(tex), 1);
			return (0);
		}
		i++;
	}
	free_textures(tex);
	return (1);
}
