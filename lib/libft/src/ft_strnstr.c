/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:07:40 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/14 12:54:21 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	strnstr -- locate a substring in a string							*/
/*	Arguments															*/
/*				s1: The string to be searched							*/
/*				s2: the string to search for							*/
/*	len			The max number of characters to search in haystack		*/
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[h] != '\0')
	{
		n = 0;
		while (haystack[h + n] == needle[n] && (h + n) < len)
		{
			if (haystack[h + n] == '\0' && needle[n] == '\0')
				return ((char *)&haystack[h]);
			n++;
		}
		if (needle[n] == '\0')
			return ((char *)haystack + h);
		h++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

#define LIMIT 15

int	main(void)
{
	char	*haystack;
	char	*needle;
	char	*location;

	haystack = "Istanbul's beating heart reels from deadly";
	needle = "ati";
	location = ft_strnstr(haystack, needle, LIMIT);
	if (location == NULL)
		printf("Can't find '%s' within %d characters of '%s'\n",
			needle,
			LIMIT,
			haystack);
	else
		printf("Found '%s' within %d characters of '%s'\n",
			needle,
			LIMIT,
			haystack);
	return (0);
}
*/
