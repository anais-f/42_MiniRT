#include "miniRT.h"
#include "camera.h"
#define EPSILON 1e-6

t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y)
{
	t_ray	ray;
	t_vec2	coord;

	coord.x = (2 * (float)x / (float)WIDTH_WIN - 1)  * minirt->cam.fov_scale;
	coord.y = (1 - 2 * (float)y / (float)HEIGHT_WIN) * minirt->cam.fov_scale * minirt->cam.aspect_ratio;
	ray.origin = minirt->cam.position;
	ray.direction = (t_vec3){coord.x, coord.y, 1};
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
