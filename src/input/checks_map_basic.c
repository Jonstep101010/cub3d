#include "input.h"
#include "libft.h"
#include "libutils.h"

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
	free_null(&file->lines);
	file->line_ptr = NULL;
	return (split_map && printf("split map!\n"));
}
