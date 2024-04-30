/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:06:12 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/08 22:52:49 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i1] != '\0')
	{
		str[i1] = s1[i1];
		i1++;
	}
	while (s2[i2] != '\0')
	{
		str[i1 + i2] = s2[i2];
		i2++;
	}
	str[i1 + i2] = '\0';
	return (str);
}
