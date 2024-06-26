/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fc_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:05:11 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/17 13:05:13 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_utils.h"
#include "input.h"
#include "libft.h"
#include "libutils.h"

static bool	string_is_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

static uint32_t	rgb_arr_hex(int rgb[3])
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

static t_parse_fc	parse_fc(const char *trimmed_line)
{
	char		*tmp;
	char *const	*split = (char *const *)ft_split(trimmed_line, ',');
	size_t		size;
	int			atoi_ret[3];

	size = arr_len(split);
	if (size != 3)
		return (arr_free((char **)split), (t_parse_fc){0});
	while (size--)
	{
		tmp = ft_strtrim(split[size], ", ");
		if (!tmp || ft_strlen(tmp) > 3 || !*tmp || !string_is_digit(tmp))
			return (arr_free((char **)split), free(tmp), (t_parse_fc){0});
		atoi_ret[size] = ft_atoi(tmp);
		free_null(&tmp);
		if (atoi_ret[size] > UINT8_MAX || atoi_ret[size] < 0)
			return (arr_free((char **)split), (t_parse_fc){0});
	}
	arr_free((char **)split);
	return ((t_parse_fc){
		.set = true, .color = rgb_arr_hex(atoi_ret),
	});
}

bool	check_fc_colors(const char *line, t_cube_file *file)
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
