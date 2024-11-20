#include "miniRT.h"
#include "camera.h"

// t_ray create_ray(t_camera cam, t_vec2 coord)
// {
// 	t_ray ray;

// 	ray.origin = cam.position;

// 	ray.direction = cam.direction;


// 	float fov_scale = tan(cam.FOV * 0.5); // a mettre dans t_camera

// 	/* ray */

// 	coord.px = (2 * (coord.px + 0.5) / (float)WIDTH_WIN - 1) * cam.ratio * fov_scale;
// 	coord.py = (1 - 2 * (coord.py + 0.5) / (float)HEIGHT_WIN) * fov_scale;


// 	return (ray);
// }


t_ray	create_ray(t_minirt *minirt, int x, int y)
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
	t_hit	hit;	 // a initialiser

	get_ambient_light(minirt); // a ressortir avec le parsing

	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			// on va afficher l'objet le plus proche en premier
			ft_memset(&hit, 0, sizeof(t_hit));
			hit.dst = -1;

			ray = create_ray(minirt, x, y);
		
			int i = 0;
			while (i < 3)
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
			minirt->color = get_color_object_pixel(minirt, hit);// calculer la lumiere


			my_mlx_pixel_put(img, x, y, minirt->color.color);
			x++;
		}
		y++;
	}
}
