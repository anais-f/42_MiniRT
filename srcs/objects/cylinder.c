#include "miniRT.h"

double cylinder_intersection(t_ray ray, t_object cylinder, t_hit *hit)
{
	t_vec3 offset_ray_origin, ray_dir_proj, offset_ray_origin_proj, cap_point;
	double abc[3], discriminant, t0, t1, t_cap[2];
	t_vec3 cap_positions[2];
	double height = cylinder.spec.cylinder.height;
	double radius = cylinder.spec.cylinder.radius;

	// Positions des capuchons
	cap_positions[0] = cylinder.position; // Cap inférieur
	cap_positions[1] = add_vec3(cylinder.position, mult_nb_vec3(cylinder.direction, height)); // Cap supérieur

	// Intersection avec le corps du cylindre
	offset_ray_origin = sub_vec3(ray.origin, cylinder.position);
	ray_dir_proj = sub_vec3(ray.direction, mult_nb_vec3(cylinder.direction, dot_vec3(ray.direction, cylinder.direction)));
	offset_ray_origin_proj = sub_vec3(offset_ray_origin, mult_nb_vec3(cylinder.direction, dot_vec3(offset_ray_origin, cylinder.direction)));
	abc[0] = dot_vec3(ray_dir_proj, ray_dir_proj);
	abc[1] = 2 * dot_vec3(ray_dir_proj, offset_ray_origin_proj);
	abc[2] = dot_vec3(offset_ray_origin_proj, offset_ray_origin_proj) - (radius * radius);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];

	t0 = -1;
	t1 = -1;
	if (discriminant >= 0)
	{
		t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
		t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);

		// Filtrer les intersections en dehors des limites de hauteur
		t_vec3 point_t0 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t0));
		t_vec3 point_t1 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t1));

		if (t0 < 0 || dot_vec3(sub_vec3(point_t0, cylinder.position), cylinder.direction) < 0 ||
			dot_vec3(sub_vec3(point_t0, cap_positions[1]), cylinder.direction) > 0)
			t0 = -1;

		if (t1 < 0 || dot_vec3(sub_vec3(point_t1, cylinder.position), cylinder.direction) < 0 ||
			dot_vec3(sub_vec3(point_t1, cap_positions[1]), cylinder.direction) > 0)
			t1 = -1;
	}

	// Intersection avec les capuchons
	for (int i = 0; i < 2; i++)
	{
		double denom = dot_vec3(ray.direction, cylinder.direction);
		t_cap[i] = -1;
		if (fabs(denom) > 1e-6) // Évite la division par zéro
		{
			double t = dot_vec3(sub_vec3(cap_positions[i], ray.origin), cylinder.direction) / denom;
			if (t > 0)
			{
				cap_point = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t));
				if (distance_vec3(cap_point, cap_positions[i]) <= radius)
					t_cap[i] = t;
			}
		}
	}

	// Trouver le plus petit \( t > 0 \) et mettre à jour hit->surface_type
	double t_min = -1;
	if (t0 > 0 && (t_min < 0 || t0 < t_min))
	{
		t_min = t0;
		hit->normal = normalize_vec3(sub_vec3(add_vec3(ray.origin, mult_nb_vec3(ray.direction, t_min)), cylinder.position)); // Corps
	}
	if (t1 > 0 && (t_min < 0 || t1 < t_min))
	{
		t_min = t1;
		hit->normal = mult_nb_vec3(normalize_vec3(sub_vec3(add_vec3(ray.origin, mult_nb_vec3(ray.direction, t_min)), cylinder.position)), -1.f); // Corps peut etre normale *-1 ??
	}
	if (t_cap[0] > 0 && (t_min < 0 || t_cap[0] < t_min))
	{
		t_min = t_cap[0];
		hit->normal = mult_nb_vec3(cylinder.direction, -1.f); // Cap inférieur
	}
	if (t_cap[1] > 0 && (t_min < 0 || t_cap[1] < t_min))
	{
		t_min = t_cap[1];
		hit->normal = cylinder.direction; // Cap supérieur
	}

	return t_min;
}

t_vec3 get_normal_cylinder(t_camera cam, t_hit hit)
{
	(void)cam;
	return hit.normal;
}
