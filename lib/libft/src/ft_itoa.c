/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:55:28 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/13 22:24:58 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	num_size(int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = num_size(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n != 0)
	{
		len--;
		res[len] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
