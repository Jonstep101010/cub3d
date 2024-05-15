/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:59:16 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/15 18:00:24 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "input.h"
#include <stdlib.h>

void	free_cubed(t_cube_data *cubed)
{
	int	i;

	i = -1;
	if (!cubed)
		return ;
	while (++i < 4)
		mlx_delete_texture(cubed->res->tex[i]);
	i = -1;
	while (++i <= (int)cubed->res->map_height)
		free(cubed->res->map_lines[i].y_view);
	free(cubed->res->map_lines);
	free(cubed->res);
}
