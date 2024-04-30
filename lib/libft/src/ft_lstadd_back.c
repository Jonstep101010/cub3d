/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:31:30 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/16 17:06:00 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == 0)
		return ;
	else if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp -> next = new;
}
