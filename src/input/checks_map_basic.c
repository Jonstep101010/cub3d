#include "input.h"
#include "libft.h"
#include "libutils.h"

bool	mixed_space_zero(char * const *lines)
{
	size_t	i;
	size_t	ii;

	i = 0;
	while (lines[i])
	{
		ii = 0;
		while (lines[i][ii] && lines[i][ii + 1]) {
			if ((lines[i][ii + 1] == '0' && lines[i][ii] == ' ')
				|| (lines[i][ii] == '0' && lines[i][ii + 1] == ' '))
				return (printf("mixed zero and space\n"), true);
			ii++;
		}
		i++;
	}
	return (false);
}

/**
 * @audit moves line_ptr
 */
bool	map_has_empty_line(t_cube_file *file)
{
	size_t	i;
	size_t	len;
	bool	split_map;

	i = 0;
	split_map = false;
	while (*file->line_ptr)
	{
		i = 0;
		len = ft_strlen(*file->line_ptr);
		while (i < len && !split_map)
		{
			if (ft_strchr("01NSEW ",  **file->line_ptr))
				split_map = true;
			i++;
		}
		free(*file->line_ptr);
		file->line_ptr++;
	}
	file->line_ptr = NULL;
	return (split_map && printf("split map!\n"));
}
