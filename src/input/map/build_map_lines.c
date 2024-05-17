/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:55:00 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/17 18:49:20 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "libutils.h"

static size_t	get_line_len(char const *lnptr)
{
	size_t	len;

	len = ft_strlen(lnptr);
	while (len > 0 && lnptr[len - 1] == ' ')
		len--;
	return (len);
}

static bool	set_map_size(char *const *lnptr, size_t *width, size_t *height)
{
	size_t	len;

	while (lnptr[*height] && *lnptr[*height])
	{
		len = get_line_len(lnptr[*height]);
		if (len < 3)
			return (false);
		if (len > *width)
			*width = len;
		++*height;
	}
	return (*height > 3);
}

static void	fill_from_lineptr(t_map_line *map_lineptr,
								char *lineptr, size_t width)
{
	size_t	ii;

	ii = 0;
	while (ii <= map_lineptr->len && lineptr[ii])
	{
		if (ii <= map_lineptr->len)
			map_lineptr->y_view[ii] = lineptr[ii];
		ii++;
	}
	while (ii < width)
		map_lineptr->y_view[ii++] = ' ';
	free(lineptr);
	lineptr++;
}

uint8_t	build_map_lines(t_cube_file *file)
{
	size_t	i;

	i = 0;
	if (!set_map_size(file->line_ptr, &file->map_width, &file->map_height))
		return (1);
	file->map_lines = ft_calloc(file->map_height + 1, sizeof(t_map_line));
	if (!file->map_lines)
		return (2);
	while (i <= file->map_height && *file->line_ptr && **file->line_ptr)
	{
		file->map_lines[i].len = get_line_len(*file->line_ptr);
		file->map_lines[i].y_view = ft_calloc(
				file->map_width + 1, sizeof(char));
		if (!file->map_lines[i].y_view)
		{
			while (i--)
				free_null(&(file->map_lines[i].y_view));
			return (2);
		}
		fill_from_lineptr(&file->map_lines[i],
			*file->line_ptr, file->map_width);
		file->line_ptr++;
		i++;
	}
	return (0);
}
