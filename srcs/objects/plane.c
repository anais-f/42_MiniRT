#include "miniRT.h"

double	plane_intersection(t_minirt *minirt, t_ray ray, t_object plan)
{
	double	a;
	double	b;
	double	t;

	(void)minirt;
	a = dot_vec3(ray.direction, plan.direction);
	if (a == 0)
		return (-1);
	b = dot_vec3(plan.direction, sub_vec3(ray.origin, plan.position));
	t = -b / a;
	if (t < 0)
		return (-1);
	return (t);
}

//ax + by + cz + d = 0, avec a, b, c, et d des réels
// At + B = 0
// A = direc plan * direction camera
// B = direc plan * (position camera- position plan)
// T = -B/A -> distance entre le point d'origine et le point d'intersection	
// si t < 0, l'intersection est derriere la camera
//si a = 0, le plan est parallele a la camera, il n'y a pas d'intersection

t_vec3	get_normal_plane(t_minirt *minirt, t_hit hit)
{
	t_vec3	normal;
	double	a;

	(void)minirt;
	a = dot_vec3(minirt->cam.direction, hit.object.direction);
	if (a > 0)
		normal = mult_nb_vec3(hit.object.direction, -1.0f);
	else
		normal = hit.object.direction;
	return (normal);
}

// si le produit scalaire entre la direction de la camera et
//la direction du plan est positif, on inverse la normale
// car on veut que la normale soit dirigée vers la camera
// si le produit scalaire est negatif, on garde la normale telle quelle