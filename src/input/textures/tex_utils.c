#include "input.h"
#include "libutils.h"

void	free_textures(t_cube_textures *tex)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		free_null(&(tex->dir_nesw[i].path));
		if (tex->dir_nesw[i].tex)
			mlx_delete_texture(tex->dir_nesw[i].tex);
	}
}
