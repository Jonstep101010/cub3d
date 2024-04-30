/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:53:50 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/05 16:53:51 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//turkce aciklama: bu fonksiyon, verilen stringi ve ardindan yeni satir karakterini verilen dosya tanimlayicisina yazar.
//english description: this function writes the given string and then a newline character to the given file descriptor.
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
