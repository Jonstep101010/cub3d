/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:48:14 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/16 17:09:16 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*link;

	link = malloc(sizeof(t_list));
	if (!link)
		return (0);
	link -> content = content;
	link -> next = NULL;
	return (link);
}
