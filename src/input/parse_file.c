#include "cubed.h"
#include "input.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libutils.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>

void	free_file_data(t_cube_file *data, void *nullable)
{
	free_null(&(data->tex_wall.path_north));
	free_null(&(data->tex_wall.path_east));
	free_null(&(data->tex_wall.path_south));
	free_null(&(data->tex_wall.path_west));
	while (*data->line_ptr)
	{
		free(*data->line_ptr);
		data->line_ptr++;
	}
	free(data);
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

uint8_t	parse_non_map(t_cube_file *file, char * const *lines);
uint8_t	parse_map(t_cube_file *file);

uint8_t	parse_file(t_cube_data *data, const char *path_to_file)
{
	const int	fd = open_cubefile(path_to_file);
	char		**lines;

	if (fd == -1)
		return (1);
	// create cube_file struct
	data->file = ft_calloc(1, sizeof(t_cube_file));
	if (!data->file)
		return (close(fd), EXIT_FAILURE);
	lines = read_file_lines(fd);
	if (!lines || close(fd) == -1)
		return (free(data->file), EXIT_FAILURE);
	// check contents & set values
	// @follow-up purge lines, then free lines
	if (parse_non_map(data->file, (char * const *)lines) != 0)
	{
		free_file_data(data->file, lines);
		return (1);
	}
	if (parse_map(data->file) != 0)
	{
		free_file_data(data->file, lines);
		return (1);
	}
	return (free(lines), 0);
}
