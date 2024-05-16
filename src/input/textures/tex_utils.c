/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:54:08 by jschwabe          #+#    #+#             */
/*   Updated: 2024/05/16 18:54:09 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libutils.h"

void	free_textures(t_cube_textures *tex)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		free_null(&(tex->s_dir_nesw[i].path));
		if (tex->s_dir_nesw[i].tex)
			mlx_delete_texture(tex->s_dir_nesw[i].tex);
	}
}
