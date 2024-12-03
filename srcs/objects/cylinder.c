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
	// t_vec3 normal;
	(void)cam;
	// if (isnan(hit.normal.x) || isnan(hit.normal.y) || isnan(hit.normal.z))
	// 	printf("hit.normal: %f %f %f dist : %f\n", hit.normal.x, hit.normal.y, hit.normal.z, hit.dst);
	// // if (hit.surface_type == 0) // Corps
	// {
	// 	t_vec3 proj = add_vec3(hit.object.position,
	// 		mult_nb_vec3(hit.object.direction,
	// 					 dot_vec3(sub_vec3(hit.position, hit.object.position), hit.object.direction)));
	// 	normal = normalize_vec3(sub_vec3(hit.position, proj));
	// }
	// else if (hit.surface_type == 1) // Cap inférieur
	// {
	// 	normal = mult_nb_vec3(hit.object.direction, -1);
	// }
	// else if (hit.surface_type == 2) // Cap supérieur
	// {
	// 	normal = hit.object.direction;
	// }

	return hit.normal;
}


// typedef struct s_intersection {
// 	double t;		// Distance d'intersection
// 	t_vec3 normal;	// Normale au point d'intersection
// } t_intersection;

// t_intersection cylinder_intersection(t_ray ray, t_object cylinder)
// {
// 	t_vec3 offset_ray_origin, ray_dir_proj, offset_ray_origin_proj, base_top;
// 	double abc[3], discriminant, t0, t1, t_cap;
// 	t_vec3 point_t0, point_t1, point_cap, normal;
// 	double height = cylinder.spec.cylinder.height;
// 	t_vec3 cap_positions[2] = {cylinder.position, base_top};	// Bases
// 	t_intersection result = { -1, {0, 0, 0} };					// Initialisation du résultat

// 	// Calcul des bases du cylindre
// 	base_top = add_vec3(cylinder.position, mult_nb_vec3(cylinder.direction, height));

// 	// Intersection avec le cylindre infini
// 	offset_ray_origin = sub_vec3(ray.origin, cylinder.position);
// 	ray_dir_proj = sub_vec3(ray.direction, mult_nb_vec3(cylinder.direction, dot_vec3(ray.direction, cylinder.direction)));
// 	offset_ray_origin_proj = sub_vec3(offset_ray_origin, mult_nb_vec3(cylinder.direction, dot_vec3(offset_ray_origin, cylinder.direction)));
// 	abc[0] = dot_vec3(ray_dir_proj, ray_dir_proj);
// 	abc[1] = 2 * dot_vec3(ray_dir_proj, offset_ray_origin_proj);
// 	abc[2] = dot_vec3(offset_ray_origin_proj, offset_ray_origin_proj) - (cylinder.spec.cylinder.radius * cylinder.spec.cylinder.radius);
// 	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];

// 	t0 = -1;
// 	t1 = -1;
// 	if (discriminant >= 0)
// 	{
// 		t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
// 		t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);

// 		// Vérification des limites de hauteur
// 		point_t0 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t0));
// 		point_t1 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t1));

// 		if (dot_vec3(sub_vec3(point_t0, cylinder.position), cylinder.direction) < 0 ||
// 			dot_vec3(sub_vec3(point_t0, base_top), cylinder.direction) > 0)
// 			t0 = -1;

// 		if (dot_vec3(sub_vec3(point_t1, cylinder.position), cylinder.direction) < 0 ||
// 			dot_vec3(sub_vec3(point_t1, base_top), cylinder.direction) > 0)
// 			t1 = -1;
// 	}

// 	// Intersection avec les capuchons
// 	t_cap = -1;
// 	for (int i = 0; i < 2; i++)
// 	{
// 		double denom = dot_vec3(ray.direction, cylinder.direction);
// 		if (fabs(denom) > 1e-6) // Éviter la division par zéro
// 		{
// 			double t = dot_vec3(sub_vec3(cap_positions[i], ray.origin), cylinder.direction) / denom;
// 			if (t > 0)
// 			{
// 				point_cap = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t));
// 				if (distance_vec3(point_cap, cap_positions[i]) <= cylinder.spec.cylinder.radius)
// 				{
// 					if (t_cap < 0 || t < t_cap)
// 					{
// 						t_cap = t;
// 						normal = (i == 0) ? mult_nb_vec3(cylinder.direction, -1) : cylinder.direction; // Normale du capuchon
// 					}
// 				}
// 			}
// 		}
// 	}

// 	// Déterminer la plus petite intersection valide
// 	double t_min = -1;
// 	if (t0 > 0)
// 	{
// 		t_min = t0;
// 		normal = sub_vec3(point_t0, add_vec3(cylinder.position,
// 				mult_nb_vec3(cylinder.direction, dot_vec3(sub_vec3(point_t0, cylinder.position), cylinder.direction))));
// 		normal = normalize_vec3(normal); // Normale du corps
// 	}
// 	if (t1 > 0 && (t_min < 0 || t1 < t_min))
// 	{
// 		t_min = t1;
// 		normal = sub_vec3(point_t1, add_vec3(cylinder.position,
// 				mult_nb_vec3(cylinder.direction, dot_vec3(sub_vec3(point_t1, cylinder.position), cylinder.direction))));
// 		normal = normalize_vec3(normal); // Normale du corps
// 	}
// 	if (t_cap > 0 && (t_min < 0 || t_cap < t_min))
// 	{
// 		t_min = t_cap;
// 	}

// 	// Remplir le résultat
// 	result.t = t_min;
// 	result.normal = normal;
// 	return result;
// }


// double	cylinder_intersection(t_ray ray, t_object cylinder)
// {
// 	t_vec3	offset_ray_origin;
// 	t_vec3	ray_dir_proj;
// 	t_vec3	offset_ray_origin_proj;
// 	t_vec3	base_top;
// 	double	abc[3];
// 	double	discriminant;
// 	double	t0, t1, t_cap;
// 	t_vec3	point_t0, point_t1, point_cap;
// 	double	height = cylinder.spec.cylinder.height;

// 	// Calcul des bases du cylindre
// 	base_top = add_vec3(cylinder.position, mult_nb_vec3(cylinder.direction, height));
// 	// base_down = mult_nb_vec3(base_top, -1.0f);

// 	// Intersection avec le cylindre infini
// 	offset_ray_origin = sub_vec3(ray.origin, cylinder.position);
// 	ray_dir_proj = sub_vec3(ray.direction, mult_nb_vec3(cylinder.direction, dot_vec3(ray.direction, cylinder.direction)));
// 	offset_ray_origin_proj = sub_vec3(offset_ray_origin, mult_nb_vec3(cylinder.direction, dot_vec3(offset_ray_origin, cylinder.direction)));
// 	abc[0] = dot_vec3(ray_dir_proj, ray_dir_proj);
// 	abc[1] = 2 * dot_vec3(ray_dir_proj, offset_ray_origin_proj);
// 	abc[2] = dot_vec3(offset_ray_origin_proj, offset_ray_origin_proj) - (cylinder.spec.cylinder.radius * cylinder.spec.cylinder.radius);
// 	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];

// 	t0 = -1;
// 	t1 = -1;
// 	if (discriminant >= 0)
// 	{
// 		t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
// 		t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);

// 		// Calcul des points d'intersection pour le cylindre infini
// 		point_t0 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t0));
// 		point_t1 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t1));

// 		// Vérification : les points doivent être dans les limites de la hauteur
// 		if (dot_vec3(sub_vec3(point_t0, cylinder.position), cylinder.direction) < 0 || 
// 			dot_vec3(sub_vec3(point_t0, base_top), cylinder.direction) > 0)
// 			t0 = -1; // Hors des limites
// 		if (dot_vec3(sub_vec3(point_t1, cylinder.position), cylinder.direction) < 0 || 
// 			dot_vec3(sub_vec3(point_t1, base_top), cylinder.direction) > 0)
// 			t1 = -1; // Hors des limites
// 	}

// 	// Intersection avec les capuchons (bases)
// 	t_cap = -1;
// 	t_vec3 cap_positions[2] = {cylinder.position, base_top}; // Bases
// 	for (int i = 0; i < 2; i++)
// 	{
// 		double denom = dot_vec3(ray.direction, cylinder.direction);
// 		if (fabs(denom) > 1e-6) // Éviter la division par zéro
// 		{
// 			double t = dot_vec3(sub_vec3(cap_positions[i], ray.origin), cylinder.direction) / denom;
// 			if (t > 0)
// 			{
// 				point_cap = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t));
// 				if (distance_vec3(point_cap, cap_positions[i]) <= cylinder.spec.cylinder.radius)
// 				{
// 					if (t_cap < 0 || t < t_cap)
// 						t_cap = t; // Conserver la plus petite intersection positive
// 				}
// 			}
// 		}
// 	}

// 	// Retourner la plus petite intersection positive
// 	double t_min = -1;
// 	if (t0 > 0)
// 		t_min = t0;
// 	if (t1 > 0 && (t_min < 0 || t1 < t_min))
// 		t_min = t1;
// 	if (t_cap > 0 && (t_min < 0 || t_cap < t_min))
// 		t_min = t_cap;

// 	return t_min;
// }


// double	cylinder_intersection(t_ray ray, t_object cylinder)
// {
// 	t_vec3	offset_ray_origin;
// 	t_vec3	ray_dir_proj;
// 	t_vec3	offset_ray_origin_proj;
// 	double	abc[3];
// 	double	discriminant;
// 	double	t0, t1;
// 	t_vec3	cap_t0, cap_t1;
// 	t_vec3	base_top; // Base supérieure du cylindre

// 	// Calcul des bases du cylindre
// 	base_top = add_vec3(cylinder.position, mult_nb_vec3(cylinder.direction, (cylinder.spec.cylinder.height / 2.0f)));
// 	t_vec3 base_down = mult_nb_vec3(base_top, -1.0f);

// 	// Calcul des projections pour l'intersection avec un cylindre infini
// 	offset_ray_origin = sub_vec3(ray.origin, cylinder.position);
// 	ray_dir_proj = sub_vec3(ray.direction, mult_nb_vec3(cylinder.direction, dot_vec3(ray.direction, cylinder.direction)));
// 	offset_ray_origin_proj = sub_vec3(offset_ray_origin, mult_nb_vec3(cylinder.direction, dot_vec3(offset_ray_origin, cylinder.direction)));

// 	// Calcul des coefficients quadratiques
// 	abc[0] = dot_vec3(ray_dir_proj, ray_dir_proj);
// 	abc[1] = 2 * dot_vec3(ray_dir_proj, offset_ray_origin_proj);
// 	abc[2] = dot_vec3(offset_ray_origin_proj, offset_ray_origin_proj) - (cylinder.spec.cylinder.radius * cylinder.spec.cylinder.radius);

// 	// Discriminant
// 	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
// 	if (discriminant < 0)
// 		return (-1);

// 	// Calcul des points d'intersection pour le cylindre infini
// 	t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
// 	t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);

// 	// Calcul des points d'intersection dans l'espace
// 	cap_t0 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t0));
// 	cap_t1 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t1));

// 	// Vérification : les points doivent être dans les limites de la hauteur
// 	if (dot_vec3(sub_vec3(cap_t0, cylinder.position), cylinder.direction) < 0 || 
// 		dot_vec3(sub_vec3(cap_t0, base_down), cylinder.direction) > 0)
// 		t0 = -1; // Hors des limites

// 	if (dot_vec3(sub_vec3(cap_t1, cylinder.position), cylinder.direction) < 0 || 
// 		dot_vec3(sub_vec3(cap_t1, base_top), cylinder.direction) > 0)
// 		t1 = -1; // Hors des limites

// 	// Retourner le plus proche t valide
// 	if (t0 > 0 && (t1 < 0 || t0 < t1))
// 		return t0;
// 	if (t1 > 0)
// 		return t1;

// 	// Aucun point valide
// 	return -1;
// }


// 	offset_ray_origin = sub_vec3(ray.origin, cylinder.position); // Calcul du vecteur offset_ray_origin (différence entre origine du rayon et position du cylindre)
// 	ray_dir_proj = sub_vec3(ray.direction, mult_nb_vec3(cylinder.direction, \
// 		dot_vec3(ray.direction, cylinder.direction))); // Calcul de la projection du vecteur direction sur l'axe du cylindre
// 	offset_ray_origin_proj = sub_vec3(offset_ray_origin, mult_nb_vec3 \
// 		(cylinder.direction, dot_vec3(offset_ray_origin, cylinder.direction))); // Calcul de la projection du vecteur offset_ray_origin sur l'axe du cylindre
// 	abc[0] = dot_vec3(ray_dir_proj, ray_dir_proj);
// 	abc[1] = 2 * dot_vec3(ray_dir_proj, offset_ray_origin_proj);
// 	abc[2] = dot_vec3(offset_ray_origin_proj, offset_ray_origin_proj) \
// 		- (cylinder.spec.cylinder.radius * cylinder.spec.cylinder.radius);
// 	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
// 	if (discriminant < 0)
// 		return (-1);
// 	t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
// 	t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
// 	if (t0 < 0)
// 		t0 = t1;
// 	if (t0 < 0)
// 		return (-1);
// 	return (t0);
// }





// NORMAL DU CLYLINDRE V1

// t_vec3	get_normal_cylinder(t_camera cam, t_hit hit)
// {
// 	t_vec3	normal;
// 	t_vec3	cyl_in;

// 	normal = normalize_vec3(sub_vec3(hit.position, hit.object.position));
// 	cyl_in = sub_vec3(cam.position, hit.object.position);
// 	if (dot_vec3(cyl_in, cyl_in) <= hit.object.spec.cylinder.radius)
// 		normal = mult_nb_vec3(normal, -1.0f);
// 	return (normal);
// }
