#include "miniRT.h"

double	object_intersection(t_minirt *minirt, t_ray ray, t_object object)
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
	t_vec3	normal;

	(void)minirt;
	ft_memset(&normal, 0, sizeof(t_vec3));
	if (hit.object.type == SPHERE)
		normal = get_normal_sphere(minirt, hit);
	if (hit.object.type == PLANE)
		normal = get_normal_plane(minirt, hit);
	if (hit.object.type == CYLINDER)
		normal = get_normal_cylinder(minirt, hit);
	return (normal);
}

void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit)
{
	hit->position = add_vec3(ray.origin, mult_nb_vec3(ray.direction, hit->dst));
	hit->normal = get_normal(minirt, *hit);
}
