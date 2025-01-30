/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:13:24 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/29 13:27:40 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	plane_intersection(t_ray ray, t_object plan)
{
	double	a;
	double	b;
	double	t;

	a = dot_vec3(ray.direction, plan.direction);
	if (a == 0)
		return (-1);
	b = dot_vec3(plan.direction, sub_vec3(ray.origin, plan.position));
	t = -b / a;
	if (t < 0)
		return (-1);
	return (t);
}
/* 
ax + by + cz +d = 0 with 
a = direction of the ray, 
b = origin of the ray,
c = direction of the plane,
d = position of the plane
At + B = 0 with 
A = dot(ray.direction, plan.direction)
B = dot(plan.direction, sub(ray.origin, plan.position)
 */

t_vec3	get_normal_plane(t_camera cam, t_hit hit)
{
	t_vec3	normal;
	double	a;

	(void)cam;
	a = dot_vec3(hit.ray.direction, hit.object.direction);
	if (a > 0)
		normal = mult_nb_vec3(hit.object.direction, -1.0f);
	else
		normal = hit.object.direction;
	return (normal);
}
/* If the dot product between the direction of the camera and
plane's position is positive, we have to reverse the normal because
we want the normal to face the camera */