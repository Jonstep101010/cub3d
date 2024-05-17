
#include "structs.h"
#include "cube.h"
#include <math.h>
//rayin duvara carptigi noktayi hesaplar
void	calculate_wall_x(t_cube_data *game, double wall_distance, t_draw *draw)
{
	//Eğer ray doğu (E) veya batı (W) duvarına çarptıysa, duvarın X koordinatını hesaplamak için Y yönündeki bileşenler kullanılır: ? neden

	//Ray doğu (E) veya batı (W) duvarına çarptığında, çarpışma noktasının X koordinatını hesaplamak için Y yönündeki bileşenler kullanılır çünkü doğu ve batı duvarları dikeydir ve bu duvarlara çarpma noktası, ray'in Y ekseni boyunca kat ettiği mesafeye bağlıdır.

	if (game->texture_side == W || game->texture_side == E)
		draw->wall_x = game->player.y + wall_distance * game->ray.dir_y;
	else //degilse s ve e ise x koordinatini hesaplamak icin x i kullanir
		draw->wall_x = game->player.x + wall_distance * game->ray.dir_x;
	draw->wall_x -= floor(draw->wall_x); // sadece kesirli tarafini aliriz. floor tam kismini hesaplarken cikararak tam kismi duvarin konumu gosterir. kesirli tarafi ise

	//Örneğin, draw->wall_x değeri 0.3 ise, bu dokunun %30'luk kısmını kullanmamız gerektiğini gösterir. texture birim boyutta oldugundan tam kismi doku haritalama icin  gerekli degildir. tam kismi sadece genel koordinatlarini verir bu da hesaplamak icin gereksizdir.

	//Örneğin, eğer draw->wall_x 5.3 ise, bu aslında duvarın 5 birim ilerisinde olduğunu gösterir. Ancak, doku koordinatları için sadece 0.3 kısmı önemlidir.
}


//duvar dokusunun (texture) ekranda nasıl görüntüleneceğini belirlemek için doku koordinatlarını hesaplar.bu  fonks, çarpışma noktasının doku üzerindeki X ve Y koordinatlarını hesaplar ve doku üzerinde hangi kısmın ekranda gösterileceğini belirler.
void	calculate_texture_coordinates(t_cube_data *game, t_draw *draw)
{
	//draw->wall_x: Çarpışma noktasının kesirli X koordinatı. Bu değer 0 ile 1 arasında bir değerdir.
	draw->texture_x = (int)(draw->wall_x * \
		(double)game->res->tex[game->texture_side]->width);
	draw->texture_y = 0;
	draw->text_step = (double)game->res-> \
		tex[game->texture_side]->height / draw->height;
	if (draw->start < 0)
	{
		draw->texture_y = -draw->start * draw->text_step;
		draw->start = 0;
	}
}

double	calculate_wall_distance(t_cube *cubed)
{
	const t_dda	dist = dda(cubed);

	if (cubed->texture_side == E || cubed->texture_side == W)
		return (dist.x - cubed->ray.delta_x);
	return (dist.y - cubed->ray.delta_y);
}

void	calculate_ray_deltas(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_x = INFINITY;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = INFINITY;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}
