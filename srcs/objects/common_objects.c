#include "miniRT.h"

float	object_intersection(t_minirt *minirt, t_ray ray, t_object object)
{
	if (object.type == SPHERE)
		return (sphere_intersection(minirt, ray, object));
	if (object.type == PLANE)
		return (plane_intersection(minirt, ray, object));
	if (object.type == CYLINDER)	
		return (cylinder_intersection(minirt, ray, object));
	return (-1);
}	

t_vec3	get_normal(t_minirt *minirt, t_hit hit)
{
	(void)minirt;
	t_vec3 normal;

	ft_memset(&normal, 0, sizeof(t_vec3));
	if (hit.object.type == SPHERE)
		normal = normalize_vec3(sub_vec3(hit.position, hit.object.position));
		// les autres if a faire
	return (normal);
}

void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit)
{
	hit->position = add_vec3(ray.origin, mult_nb_vec3(ray.direction, hit->dst));
	hit->normal = get_normal(minirt, *hit);
}

