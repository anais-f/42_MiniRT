#include "miniRT.h"
#include "camera.h"
#define EPSILON 1e-6

t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y)
{
	t_ray	ray;
	float	rh;
	float	rv;

	rh = 2 * tan(minirt->cam.FOV * 0.5) / WIDTH_WIN;
	rv = 2 * tan(minirt->cam.FOV * HEIGHT_WIN / (WIDTH_WIN * 2)) / HEIGHT_WIN;
	ray.origin = minirt->cam.position;
	ray.direction.x = ((float)x - (float)WIDTH_WIN * 0.5) * rh;
	ray.direction.y = ((float)HEIGHT_WIN * 0.5 - (float)y) * rv;
	ray.direction.z = 1;
	ray.direction = normalize_vec3(ray.direction);
	return (ray);
}

static double	get_light_distance(t_vec3 p1, t_vec3 p2)
{
	double	dst;

	dst = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * \
			(p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z);
	return (dst);
}

/* Need to check if there is an object between 
	the current object and the light */
bool	check_ray_to_light(t_minirt *minirt, t_hit hit, t_vec3 light_dir)
{
	t_ray	ray;
	double	dst;
	double	light_dst;
	size_t	i;

	i = 0;
	ray.origin = hit.position;
	ray.direction = light_dir;
	ray.origin = add_vec3(ray.origin, \
				mult_nb_vec3(hit.ray.direction, -EPSILON));
	while (i < minirt->objects.size)
	{
		light_dst = get_light_distance(minirt->light.position, hit.position);
		dst = object_intersection(ray, *minirt->objects.array[i]);
		if ((dst > EPSILON) && (dst * dst) < light_dst)
			return (false);
		i++;
	}
	return (true);
}
