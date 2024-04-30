/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:55:04 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/14 10:56:48 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 	Turn in files : - 						 			     	*/
/*	Parameters: s: The string which iterate						*/
/*				f: The function to apply to each character		*/
/*	Synopsis: 												*/
/*	Create new string from modifying string with specified func */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*new_str;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (s == NULL || !f || new_str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	f(unsigned int i, char c)
{
	char	str;

	str = c + 5;
	return (str);
}

int	main(void)
{
	char	*str1;
	char	*str2;

	str1 = " 1111111a ";
	str2 = ft_strmapi(str1, *f);
	printf("%s\n", str2);
}
*/
