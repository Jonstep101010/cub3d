/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:09:09 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/16 12:51:33 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*output;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	output = (char *)malloc(sizeof(*output) * (len + 1));
	if (output == NULL)
		return (NULL);
	while (i < len)
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

/*#include <stdio.h>
#include <string.h>

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

int	main(void)
{
	char	*c1;
	char	*c2;
	char	*c3;

	c1 = "caglar";
	c2 = ft_strdup(c1);
	c3 = strdup(c1);
	printf("ft_strdub: %s \t", c2);
	printf("strdub: %s \n", c3);
}
*/
