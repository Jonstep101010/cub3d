#include "arr_utils.h"
#include "input.h"
#include "libft.h"
#include "libutils.h"

static t_parse_fc	parse_fc(const char *trimmed_line)
{
	char		*tmp;
	char *const	*split = (char *const *)ft_split(trimmed_line, ',');
	int			size;
	int			atoi_ret[3];

	size = arr_len(split);
	if (size != 3)
		return (arr_free((char **)split), (t_parse_fc){0});
	while (size--)
	{
		tmp = ft_strtrim(split[size], ", ");
		if (!tmp || ft_strlen(tmp) > 3 || !*tmp)
			return (arr_free((char **)split), free(tmp), (t_parse_fc){0});
		atoi_ret[size] = ft_atoi(tmp);
		free_null(&tmp);
		if (atoi_ret[size] > UINT8_MAX)
			return (arr_free((char **)split), (t_parse_fc){0});
	}
	arr_free((char **)split);
	return ((t_parse_fc){
		.set = true, .color.r = atoi_ret[0],
		.color.g = atoi_ret[1], .color.b = atoi_ret[2]
	});
}

bool	check_fc_colors(const char *line, t_cube_file *file)
{
	if (file->space_idx == 1 && ft_strchr("FC", *line))
	{
		if (*line == 'F')
		{
			if (file->floor.set)
				return (false);
			file->floor = parse_fc(&line[2]);
		}
		if (*line == 'C')
		{
			if (file->ceiling.set)
				return (false);
			file->ceiling = parse_fc(&line[2]);
		}
		return (true);
	}
	return (false);
}
