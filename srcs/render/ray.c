    #include "miniRT.h"
#include "camera.h"
#define EPSILON 1e-7

static double	get_light_distance(t_vec3 p1, t_vec3 p2)
{
	double	dst;

	dst = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z);
	return (dst);
}

t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y) //balayage x, balayge y 
{
	t_ray	ray;
	t_vec2	coord;

	// quand le pixel balaye est tout a gauche -1, quand il est au mileu de l'ecran ca fait 0, a droite ca fauit 1
	coord.x = (float)x / (float)WIDTH_WIN * 2.0f - 1.0f; 
	coord.x *= minirt->cam.ratio;
	coord.y = -((float)y / (float)HEIGHT_WIN * 2.0f - 1.0f);
	ray.origin = (t_vec3){0, 0, 0};
	ray.direction = normalize_vec3((t_vec3){coord.x, coord.y, 1});
	// ray.direction = normalize_vec3((t_vec3){1, 0, 0});
	return (ray);
}

// A FAIRE AVEC COORD X ET COORD.Y POUR LE FOV
// 	float fov_scale = tan(cam.FOV * 0.5); // a mettre dans t_camera
// 	coord.px = (2 * (coord.px + 0.5) / (float)WIDTH_WIN - 1) * cam.ratio * fov_scale;
// 	coord.py = (1 - 2 * (coord.py + 0.5) / (float)HEIGHT_WIN) * fov_scale;

bool	check_ray_to_light(t_minirt *minirt, t_hit hit, t_vec3 light_dir)
{
	t_ray	ray;
	double	dst;
	double	light_dst;
	size_t	i;

	i = 0;
	ray.origin = hit.position;
	ray.direction = light_dir;
	//ray.origin = add_vec3(ray.origin, mult_nb_vec3(hit.ray.direction, -EPSILON));
	while (i < minirt->objects.size)
	{
		light_dst = get_light_distance(minirt->light.position, hit.position);
		dst = object_intersection(ray, *minirt->objects.array[i]);
		if ((dst > EPSILON) && (dst * dst) < light_dst)	
			return (false); // intersecte un objet avant la lumiere
		i++;
	}
	return (true); // touche directement la lumiere
}
/*
Ajout d'un "bias" à l'origine du rayon : 
J'ai ajouté un petit décalage (bias) à l'origine du rayon en utilisant la normale de la surface à la position de l'impact (hit.normal). 
Cela garantit que le rayon ne commence pas à l'exact endroit où il pourrait interagir avec la surface de l'objet de manière erronée. 
Le vec3_add(ray.origin, vec3_multiply(hit.normal, EPSILON)) déplace légèrement l'origine du rayon dans la direction de la normale, 
évitant ainsi de fausses intersections dues à des problèmes de précision.

ou utiliser le ray.direction * - 1 au lieu de hit.normal
*/

// checker que l'objet est a une distance plus faible que la lumiere
// alculer la distance entre la hit position et la lumiere

