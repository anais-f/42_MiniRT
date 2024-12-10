#include "miniRT.h"

double	ellipsoid_intersection(t_ray ray, t_object el)
{
	t_vec3	offset_ro;
	double	abc[3];
	double	discriminant;
	double	t0;
	double	t1;

	offset_ro = sub_vec3(ray.origin, el.position);
	abc[0] = dot_vec3(div_vec3(ray.direction, el.spec.el.radius), \
				div_vec3(ray.direction, el.spec.el.radius));
	abc[1] = 2.0f * dot_vec3(div_vec3(ray.direction, el.spec.el.radius), \
				div_vec3(offset_ro, el.spec.el.radius));
	abc[2] = dot_vec3(div_vec3(offset_ro, el.spec.el.radius), \
				div_vec3(offset_ro, el.spec.el.radius)) - 1;
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

t_vec3	get_normal_ellipsoid(t_camera cam, t_hit hit)
{
	t_vec3	normal;

	(void)cam;
	normal = div_vec3(sub_vec3(hit.position, hit.object.position), \
				mult_vec3(hit.object.spec.el.radius, hit.object.spec.el.radius));
	normal = normalize_vec3(normal);
	if (dot_vec3(hit.ray.direction, normal) > 0)
		normal = mult_nb_vec3(normal, -1.0f);
	return (normal);
}
