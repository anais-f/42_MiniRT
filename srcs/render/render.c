#include "miniRT.h"
#include "camera.h"


t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y)
{
	t_ray	ray;
	t_vec2 coord;

	coord.x = (float)x / (float)WIDTH_WIN * 2.0f - 1.0f;
	coord.x *= minirt->cam.ratio;
	coord.y = -((float)y / (float)HEIGHT_WIN * 2.0f - 1.0f);
	ray.origin = minirt->cam.position;
	ray.direction = (t_vec3){coord.x, coord.y, minirt->cam.direction.z};
	return (ray);
}


void	render_scene(t_minirt *minirt, t_img *img)
{
	int		x;
	int		y;
	float	t; // distance de hit
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
			int i = 0;
			while (i < 4)
			{
				// trouver l'objet le plus proche -> recuperer la distance
				t = object_intersection(minirt,ray, minirt->object[i]); // renvoi un float pour faire le calcul pour trouver l'objet le plus proche 
				if (t != -1 && (t < hit.dst || hit.dst == -1))
				{
					hit.dst = t;
					hit.object = minirt->object[i];
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
}
