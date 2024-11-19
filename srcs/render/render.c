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
	//t_vec2	coord;

	get_ambient_light(minirt);

	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			// coord.x = (float)x / (float)WIDTH_WIN * 2.0f - 1.0f;
			// coord.x *= minirt->cam.ratio;
			// coord.y = -((float)y / (float)HEIGHT_WIN * 2.0f - 1.0f);
			
			// on va afficher l'objet le plus proche en premier
			/* initialisation de la couleur*/	
			t_color color;
			color = add_colors(minirt->ambient_light.color, minirt->light.color);
			minirt->color.r = multiply_colors(minirt->background_color, color).r;
			minirt->color.g = multiply_colors(minirt->background_color, color).g;
			minirt->color.b = multiply_colors(minirt->background_color, color).b;
			// minirt->color.r = 0;
			// minirt->color.g = 0;
			// minirt->color.b = 0;
			minirt->color.a = 0;
			// printf("color = %d %d %d\n", minirt->color.r, minirt->color.g, minirt->color.b);
			int i = 0;
			while (i < 3)
			{
				display_sphere(minirt, x, y, i); // renvoi un int pour faire le calcul pour trouver l'objet le plus proche 
				my_mlx_pixel_put(img, x, y, minirt->color.color);
				i++;
			}
			x++;
		}
		y++;
	}
}