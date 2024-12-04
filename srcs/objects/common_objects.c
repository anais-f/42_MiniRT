#include "miniRT.h"

double	object_intersection(t_ray ray, t_object object, t_hit *hit)
{
	if (object.type == SPHERE)
		return (sphere_intersection(ray, object));
	if (object.type == PLANE)
		return (plane_intersection(ray, object));
	if (object.type == CYLINDER)
		return (cylinder_intersection(ray, &object, hit));
	return (-1);
}

t_vec3	get_normal(t_camera cam, t_hit hit)
{
	t_vec3	normal;

	ft_memset(&normal, 0, sizeof(t_vec3));
	if (hit.object.type == SPHERE)
		normal = get_normal_sphere(cam, hit);
	if (hit.object.type == PLANE)
		normal = get_normal_plane(cam, hit);
	if (hit.object.type == CYLINDER)
		normal = hit.normal;
	return (normal);
}

void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit)
{
	hit->position = add_vec3(ray.origin, mult_nb_vec3(ray.direction, hit->dst));
	hit->normal = get_normal(minirt->cam, *hit);
}
