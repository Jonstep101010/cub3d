/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:06:20 by muhnal            #+#    #+#             */
/*   Updated: 2024/02/24 15:31:44 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strchr() function locates the first occurrence of c (converted to a char) in the string pointed to by s.  The terminating null character is considered to be part of the string; therefore if c is `\0', the functions locate the terminating `\0'.
// The strchr() function returns a pointer to the located character, or NULL if the character does not appear in the string.
//turkce aciklama: strchr() fonksiyonu, s ile gösterilen dize içinde c'nin (char olarak dönüştürülmüş) ilk oluşumunu bulur.  Sonlandırıcı null karakter dize parçasının bir parçası olarak kabul edilir; bu nedenle c `\0' ise, işlevler sonlandırıcı `\0'yi bulur.
char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *) s;
	while (*str != '\0')
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (*str == (char)c)
		return (str);
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
int main () {
   const char str[] = "This is just a String";
   const char ch = 'u';
   char *p;
   p = ft_strchr(str, ch);
   printf("String starting from %c is: %s", ch, p);
   return 0;
}
*/
