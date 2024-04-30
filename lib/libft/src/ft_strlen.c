/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:06:33 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/15 17:31:58 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter] != 0)
	{
		counter++;
	}
	return (counter);
}

/* ************************************************************************** *
**
** 7.24.6.3 [The strlen function]
**
** 1 Synopsis
** 		#include <string.h>
** 		size_t strlen(const char *s);
** Description
**		The strlen function computes the length of the string pointed to by s.
** Returns
** 		The strlen function returns the number of characters that precede the
** 		terminating null character.
*/
