/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:07:52 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/16 08:17:51 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
       The  strcmp()  function compares the two strings s1 and s2.The comparison
	   is done using unsigned characters.strcmp() returns an integer indicating
	   the result of the comparison, as follows:

       • 0, if the s1 and s2 are equal;

       • a negative value if s1 is less than s2;

       • a positive value if s1 is greater than s2.

       The strncmp() function is similar, except it compares only the first
	   (at most) n bytes of s1 and s2.

*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 != '\0' && *s1 == *s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
