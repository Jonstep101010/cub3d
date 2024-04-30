/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:05:12 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/15 17:09:20 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		c = (c + 32);
	return (c);
}

/*
** The tolower() function takes an uppercase alphabet and convert it to a 
lowercase character.
** If the arguments passed to the tolower() function is other than an 
uppercase alphabet,
** it returns the same character that is passed to the function.
** It is defined in ctype.h header file.
*/
