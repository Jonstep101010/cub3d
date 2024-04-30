/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:06:39 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/14 16:29:12 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t		i;

	i = 0;
	if (s && f)
	{
		while (s[i])
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}

/*
#include <stdio.h>

void f(unsigned int i, char *s)
{
	s[i]++;
}

int main(void)
{
	char str1[1] = "z";

	ft_striteri(str1, *f);
	printf("%s\n", str1);
}
*/
