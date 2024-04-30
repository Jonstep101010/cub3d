/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:11:01 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/15 17:11:07 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c = (c - 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
int main() {
	char c;

	c = 'm';
	printf("%c -> %c", c, toupper(c));

	c = 'D';
	printf("\n%c -> %c", c, toupper(c));

	c = '9';
	printf("\n%c -> %c", c, toupper(c));
	return 0;
}


The toupper() function converts a lowercase alphabet to an uppercase alphabet.

The function prototype of the toupper() function is:
*/
