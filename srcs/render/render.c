#include "miniRT.h"
#include "camera.h"

void	render_scene(t_minirt *minirt, t_img *img)
{
	int		x;
	int		y;
	size_t	i;
	double	dst;
	t_ray	ray;
	t_hit	hit;

	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			// on va afficher l'objet le plus proche en premier
			ft_memset(&hit, 0, sizeof(t_hit));
			hit.dst = -1;

			ray = create_ray_from_cam(minirt, x, y);
			hit.ray = ray; // pour recuperer le ray pour le calcul de l'ombre
			i = 0;
			while (i < minirt->objects.size)
			{
				// trouver l'objet le plus proche -> recuperer la distance
				dst = object_intersection(ray, *minirt->objects.array[i]); // renvoi un double pour faire le calcul pour trouver l'objet le plus proche 
				if (dst != -1 && (dst < hit.dst || hit.dst == -1))
				{
					hit.dst = dst;
					hit.object = *minirt->objects.array[i];
				}
				i++;
			}
			hit_point(minirt, ray, &hit); // calculer mon intersection et la normale
			minirt->color = get_color_pixel(minirt, hit);// calculer la couleur du pixel
			my_mlx_pixel_put(img, x, y, minirt->color.color);
			x++;
		}
		y++;
	}
	//printf("render done\n");
}
