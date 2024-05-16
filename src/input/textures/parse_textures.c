#include "input.h"
#include "libft.h"
#include "libutils.h"
#include <fcntl.h>

static bool	load_textures(t_cube_textures *tex)
{
	int				i;

	i = -1;
	while (++i < 4)
	{
		tex->s_dir_nesw[i].tex = mlx_load_png(tex->s_dir_nesw[i].path);
		free_null(&tex->s_dir_nesw[i].path);
		if (!tex->s_dir_nesw[i].tex)
		{
			while (i-- > 0)
			{
				free_null(&tex->s_dir_nesw[i].path);
				mlx_delete_texture(tex->s_dir_nesw[i].tex);
			}
			return (false);
		}
	}
	tex->set = true;
	return (true);
}

void	free_textures(t_cube_textures *tex);

/**
 * @brief make sure there are textex for each direction
 */
static uint8_t	check_paths_differ(char **path,
	t_cube_textures *tex, int direction)
{
	int				i;
	const size_t	len = ft_strlen(*path);

	i = 0;
	while (i < 4)
	{
		if (i != direction)
		{
			if (tex->s_dir_nesw[i].path && len == ft_strlen(tex->s_dir_nesw[i].path)
				&& ft_strnstr(*path, tex->s_dir_nesw[i].path, len))
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
	t_cube_textures *tex, int direction)
{
	char	**path;
	int		fd;

	path = &(tex->s_dir_nesw[direction].path);
	if (*path)
		return (free_textures(tex), 1);
	*path = ft_strtrim(line + 2, " ");
	if (!*path || !**path)
		return (free_textures(tex), 1);
	if (check_paths_differ(path, tex, direction) != 0)
		return (free_textures(tex), 1);
	fd = open(*path, O_RDONLY);
	if (fd == -1)
		return (free_textures(tex), 1);
	close(fd);
	return (tex->s_dir_nesw[0].path
		&& tex->s_dir_nesw[1].path
		&& tex->s_dir_nesw[2].path
		&& tex->s_dir_nesw[3].path
		&& !load_textures(tex)
	);
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
			if (tex_direction(line, tex, i) != 0)
			{
				free_textures(tex);
				return (1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}
