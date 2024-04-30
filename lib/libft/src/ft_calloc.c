/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:03:04 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/21 10:11:06 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION:
** 		The calloc() function contiguously allocates enough space for count
**	objects that are size bytes of memory each and returns a pointer to the
**	allocated memory. The allocated memory is filled with bytes of value
**	zero.
*/

// RETURN VALUES
//      If successful, calloc() function returns a pointer to allocated memory.
//		If there is an error, they return a NULL pointer and set errno to
//		ENOMEM.
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*dst;

	total_size = size * count;
	dst = malloc(total_size);
	if (!dst)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_memset(dst, 0, total_size);
	return (dst);
}
