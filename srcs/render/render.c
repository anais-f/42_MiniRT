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

void	render_scene(t_minirt *minirt, t_img *img)
{
	int 	x;
	int		y;

	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			// on va afficher l'objet le plus proche en premier
		
			display_sphere(minirt, x, y); // renvoi un int pour faire le calcul pour trouver l'objet le plus proche 
			my_mlx_pixel_put(img, x, y, minirt->color.color);
			x++;
		}
		y++;
	}
}