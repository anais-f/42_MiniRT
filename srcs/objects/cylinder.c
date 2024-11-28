#include "miniRT.h"

double	cylinder_intersection(t_ray ray, t_object cylinder)
{
	t_vec3	offset_ray_origin;
	t_vec3	ray_dir_proj;
	t_vec3	offset_ray_origin_proj;
	double	abc[3];
	double	discriminant;
	double	t0;
	double t1;

	offset_ray_origin = sub_vec3(ray.origin, cylinder.position); // Calcul du vecteur offset_ray_origin (différence entre origine du rayon et position du cylindre)
	ray_dir_proj = sub_vec3(ray.direction, mult_nb_vec3(cylinder.direction, \
		dot_vec3(ray.direction, cylinder.direction))); // Calcul de la projection du vecteur direction sur l'axe du cylindre
	offset_ray_origin_proj = sub_vec3(offset_ray_origin, mult_nb_vec3 \
		(cylinder.direction, dot_vec3(offset_ray_origin, cylinder.direction))); // Calcul de la projection du vecteur offset_ray_origin sur l'axe du cylindre
	abc[0] = dot_vec3(ray_dir_proj, ray_dir_proj);
	abc[1] = 2 * dot_vec3(ray_dir_proj, offset_ray_origin_proj);
	abc[2] = dot_vec3(offset_ray_origin_proj, offset_ray_origin_proj) \
		- (cylinder.spec.cylinder.radius * cylinder.spec.cylinder.radius);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (-1);
	t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (t0 < 0)
		t0 = t1;
	if (t0 < 0)
		return (-1);
	return (t0);
}

t_vec3	get_normal_cylinder(t_camera cam, t_hit hit)
{
	t_vec3	normal;
	t_vec3	cyl_in;

	normal = normalize_vec3(sub_vec3(hit.position, hit.object.position));
	cyl_in = sub_vec3(cam.position, hit.object.position);
	if (dot_vec3(cyl_in, cyl_in) <= hit.object.spec.cylinder.radius)
		normal = mult_nb_vec3(normal, -1.0f);
	return (normal);
}
