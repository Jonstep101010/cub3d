/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:06:16 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/15 16:59:51 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n > 0)
	{
		p[n - 1] = c;
		n--;
	}
	return (ptr);
}

/*
**   ptr − This is a pointer to the block of memory to fill.
**   c − This is the value to be set. The value is passed as an int,
	but the function fills the block of memory using the unsigned
	char conversion of this value.
**
**     n − Number of bytes to be filled starting point to filling in ptr
	with "int c".
*/
