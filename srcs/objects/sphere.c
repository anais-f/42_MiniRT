#include "miniRT.h"

double	sphere_intersection(t_ray ray, t_object sphere)
{
	t_vec3	offset_ray_origin;
	double	abc[3];
	double	discriminant;
	double	t0;
	double	t1;

	offset_ray_origin = sub_vec3(ray.origin, sphere.position);
	abc[0] = dot_vec3(ray.direction, ray.direction);
	abc[1] = 2.0f * dot_vec3(offset_ray_origin, ray.direction);
	abc[2] = dot_vec3(offset_ray_origin, offset_ray_origin) - \
				sphere.spec.sphere.radius * sphere.spec.sphere.radius;
	discriminant = abc[1] * abc[1] - 4.0f * abc[0] * abc[2];
	if (discriminant < 0.f)
		return (-1);
	t0 = (-abc[1] - sqrt(discriminant)) / (2.0f * abc[0]);
	t1 = (-abc[1] + sqrt(discriminant)) / (2.0f * abc[0]);
	if (t0 < 0)
		t0 = t1;
	if (t0 < 0)
		return (-1);
	return (t0);
}

/*
(bx^2 +by^2)t^2 + (2bxax + 2byay)t + (ax^2 + ay^2 - r^2) = 0 
-> resolution of the equation with a, b and c :
t = distance beetwen the origin of the ray and the intersection point
a = origin of the ray
b = direction of the ray
r = radius of the sphere
*/

t_vec3	get_normal_sphere(t_camera cam, t_hit hit)
{
	t_vec3	normal;
	t_vec3	sphere_in;

	normal = normalize_vec3(sub_vec3(hit.position, hit.object.position));
	sphere_in = sub_vec3(cam.position, hit.object.position);
	if (dot_vec3(sphere_in, sphere_in) <= hit.object.spec.sphere.radius)
		normal = mult_nb_vec3(normal, -1.0f);
	return (normal);
}
