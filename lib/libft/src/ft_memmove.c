/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:06:12 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/16 11:24:41 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
	{
		return (0);
	}
	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

/*
DESCRIPTION
       The memmove() function copies n bytes from memory area src to memory area
dest.  The memory areas may overlap: copying takes place as though the
bytes in src are first copied into a temporary array that does not overlap
src or dest,and the bytes are then copied from the temporary array to dest.

RETURN VALUE
       The memmove() function returns a pointer to dest.
*/
