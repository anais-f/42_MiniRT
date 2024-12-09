/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:36 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/09 17:56:37 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define EPSILON 1e-6

t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y)
{
	t_ray	ray;
	t_vec2	coord;

	coord.x = (2 * (float)x / (float)WIDTH_WIN - 1) * minirt->cam.fov_scale;
	coord.y = (1 - 2 * (float)y / (float)HEIGHT_WIN) * minirt->cam.fov_scale \
		* minirt->cam.aspect_ratio;
	ray.origin = minirt->cam.position;
	ray.direction = (t_vec3){coord.x, coord.y, 1};
	ray.direction = normalize_vec3(ray.direction);
	return (ray);
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
		light_dst = distance_vec3(minirt->light.position, hit.position);
		dst = object_intersection(ray, *minirt->objects.array[i], &hit);
		if ((dst > EPSILON) && (dst * dst) < light_dst)
			return (false);
		i++;
	}
	return (true);
}
