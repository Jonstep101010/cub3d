/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:06:00 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/15 18:35:46 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((void *) p + i);
		i++;
	}
	return (0);
}

/* DESCRIPTION
       The  memchr()  function scans the initial n bytes of the memory area
	   pointed to by s for the first instance of c.  Both c and the bytes of
	   the memory area pointed to by s are interpreted as unsigned char.
	   Parameters:

	s: This is a pointer to the object to be searched for.
	c: This is a character to search for.
	n: Max number of the byte which is examined to search c.

*/
