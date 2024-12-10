#include "miniRT.h"

void	init_ellips(t_minirt *minirt)
{
	minirt->cam.position = (t_vec3){0.f, 0.f, -3.f};
	minirt->cam.direction = (t_vec3){0.f, 0.f, 1.f};

	minirt->color.r = 0;
	minirt->color.g = 0;
	minirt->color.b = 0;
	minirt->color.a = 0;
	minirt->light.position = (t_vec3){0.f, 0.f, -2.f};
	minirt->light.brightness = 1.0f; // entre 0 et 1

	//RGB non necessaire dans le mandatory
	minirt->light.color.b = 255;
	minirt->light.color.g = 255;
	minirt->light.color.r = 255;
	minirt->light.color.a = 0;

	minirt->ambient_light.color.b = 255;
	minirt->ambient_light.color.g = 255;
	minirt->ambient_light.color.r = 255;
	minirt->ambient_light.color.a = 0;
	minirt->ambient_light.brightness = 0.3f;

	minirt->obj.type = ELLIPSOID;
	minirt->obj.position = (t_vec3){0.f, 0.f, 0.f};
	minirt->obj.direction = (t_vec3){0.f, 0.f, 0.f};
	minirt->obj.color.b = 255;
	minirt->obj.color.g = 0;
	minirt->obj.color.r = 255;
	minirt->obj.color.a = 0;
	minirt->obj.spec.ellipsoid.half_axis = (t_vec3){2.f, 1.5f, 2.f};
}

double	ellipsoid_intersection(t_ray ray, t_object ellipsoid)
{
	t_vec3	offset_ro;
	double	abc[3];
	double	discriminant;
	double	t0;
	double	t1;
	t_vec3	a;

	a = div_vec3(ray.direction, ellipsoid.spec.ellipsoid.half_axis);

	offset_ro = sub_vec3(ray.origin, ellipsoid.position);
	abc[0] = dot_vec3(a,a);
	abc[1] = 2.0f * dot_vec3(a, div_vec3(offset_ro, ellipsoid.spec.ellipsoid.half_axis));
	abc[2] = 

	
}





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




















//COPILOTED

double	ellips_intersection(t_ray ray, t_object ellipsoid)
{
	t_vec3	offset_ray_origin;
	double	abc[3];
	double	discriminant;
	double	t0;
	double	t1;

	offset_ray_origin = sub_vec3(ray.origin, ellipsoid.position);
	abc[0] = dot_vec3(ray.direction, ray.direction);
	abc[1] = 2.0f * dot_vec3(offset_ray_origin, ray.direction);
	abc[2] = dot_vec3(offset_ray_origin, offset_ray_origin) - \
				ellipsoid.spec.ellipsoid.radius * ellipsoid.spec.ellipsoid.radius;
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