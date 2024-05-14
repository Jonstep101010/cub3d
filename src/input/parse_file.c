#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libutils.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>

void	free_textures(t_cube_textures *tex);

/**
 * @audit moves line_ptr for the last time
 */
void	free_file_data(t_cube_file *file, void *nullable)
{
	int		i;

	free_textures(&file->tex_wall);
	i = 0;
	while (file->map_lines && file->map_lines[i].y_view)
	{
		free(file->map_lines[i].y_view);
		i++;
	}
	free(file->map_lines);
	while (*file->line_ptr)
	{
		free(*file->line_ptr);
		file->line_ptr++;
	}
	if (nullable)
		free(nullable);
}

static int	open_cubefile(const char *path_to_file)
{
	const size_t	len = secure_strlen(path_to_file);
	int				fd;

	if (len < 5 || ft_strncmp(".cub", &path_to_file[len - 4], 4))
	{
		printf("error\n");
		return (-1);
	}
	fd = open(path_to_file, O_RDONLY);
	if (fd == -1)
	{
		printf("error\n");
	}
	return (fd);
}

static char	**read_file_lines(int fd)
{
	char	**arr_lines;
	char	*line;
	char	*line_no_nl;

	arr_lines = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (arr_lines);
		line_no_nl = ft_strtrim(line, "\n");
		arr_lines = append_str_arr_free(arr_lines, line_no_nl);
		free_null(&line);
		if (!arr_lines)
			return (NULL);
	}
	return (NULL);
}

uint8_t		parse_non_map(t_cube_file *file, char * const *lines);
uint8_t		parse_map(t_cube_file *file);
uint32_t	srgb_hex(t_rgb color);

static t_parse_res	*create_res(t_cube_file *file, char **lines)
{
	t_parse_res			*res;
	const t_parse_res	stacked =
	{
		.map_width = file->map_width,
		.map_height = file->map_height,
		.tex = {
			file->tex_wall.dir_nesw[0].tex,
			file->tex_wall.dir_nesw[1].tex,
			file->tex_wall.dir_nesw[2].tex,
			file->tex_wall.dir_nesw[3].tex
		},
		.floor = srgb_hex(file->floor.color),
		.ceiling = srgb_hex(file->ceiling.color),
		.map_lines = file->map_lines,
	};

	res = ft_calloc(1, sizeof(t_parse_res));
	if (!res)
		return (free_file_data(file, lines), NULL);
	ft_memcpy(res, &stacked, sizeof(t_parse_res));
	return (res);
}

uint8_t	parse_file(t_cube_data *data, const char *path_to_file)
{
	const int	fd = open_cubefile(path_to_file);
	char		**lines;
	t_cube_file	file;

	file = (t_cube_file){0};
	if (fd == -1)
		return (1);
	lines = read_file_lines(fd);
	if (!lines || close(fd) == -1)
		return (EXIT_FAILURE);
	if (parse_non_map(&file, (char * const *)lines) != 0)
	{
		free_file_data(&file, lines);
		return (1);
	}
	if (parse_map(&file) != 0)
	{
		free_file_data(&file, lines);
		return (1);
	}
	data->res = create_res(&file, lines);
	if (!data->res)
		return (1);
	ft_memcpy(&data->player, &file.player, sizeof(t_player));
	return (free(lines), 0);
}
