/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_main copy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:06:29 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/14 09:53:13 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	if (i < size -1 && src[i] != '\0')
	{
		while (src[i] != '\0' && i < size -1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

/*
The strlcpy() function copies up to "size - 1" characters from
the NUL-terminated string src to dst, NUL-terminating the result.

RETURN VALUE
	Size of string SRC
*/
