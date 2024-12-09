#include "miniRT.h"

// voir les commentaires qui sont en francais fgdsggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg

t_vec3	get_normal_cy_at_pos(t_ray ray, t_object *cy, double t_min, int flag)
{
	double	offset_hypo;
	t_vec3	hit_position;
	double	offset;
	t_vec3	tmp_hit_position;

	if (flag == 0)
	{
		hit_position = mult_nb_vec3(ray.direction, t_min);
		hit_position = add_vec3(ray.origin, hit_position);
		offset_hypo = distance_vec3(hit_position, cy->position);
		offset = offset_hypo - (cy->spec.cy.radius * cy->spec.cy.radius);
		offset = sqrtf(offset);
		if (isnan(offset))
			offset = 0;
		tmp_hit_position = sub_vec3(hit_position, \
			mult_nb_vec3(cy->direction, offset));
		return (normalize_vec3(sub_vec3(tmp_hit_position, cy->position)));
	}
	else if (flag == 1)
		return (mult_nb_vec3(normalize_vec3(sub_vec3(add_vec3(ray.origin, \
			mult_nb_vec3(ray.direction, t_min)), cy->position)), -1.f));
	else if (flag == 2)
		return (mult_nb_vec3(cy->direction, -1.f));
	return ((cy->direction));
}
/*
Retourne la normale du cylindre en fonction de la position de l'intersection
flag == 0 corps
flag == 1 corps en etant a l'interieur du cylindre (normale * -1 ?)
flag == 2 cap inferieur
flag == 3 cap sup.
*/

static void	calculate_body_intersections(t_ray ray, t_object *cy, double radius)
{
	double	abc[3];
	double	discriminant;
	t_vec3	offset_ray_og;
	t_vec3	ray_dir_proj;
	t_vec3	offset_ray_origin_proj;

	offset_ray_og = sub_vec3(ray.origin, cy->position);
	ray_dir_proj = sub_vec3(ray.direction, mult_nb_vec3(cy->direction, \
		dot_vec3(ray.direction, cy->direction)));
	offset_ray_origin_proj = sub_vec3(offset_ray_og, \
		mult_nb_vec3(cy->direction, dot_vec3(offset_ray_og, cy->direction)));
	abc[0] = dot_vec3(ray_dir_proj, ray_dir_proj);
	abc[1] = 2 * dot_vec3(ray_dir_proj, offset_ray_origin_proj);
	abc[2] = dot_vec3(offset_ray_origin_proj, offset_ray_origin_proj) - \
		(radius * radius);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	cy->spec.cy.t0 = -1;
	cy->spec.cy.t1 = -1;
	if (discriminant >= 0)
	{
		cy->spec.cy.t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
		cy->spec.cy.t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	}
	return ;
}
/*Calcul des intersections avec le corps du cylindre*/

static void	filter_body_intersections(t_ray ray, t_object *cy)
{
	t_vec3	point_t0;
	t_vec3	point_t1;

	if (cy->spec.cy.t0 >= 0)
	{
		point_t0 = add_vec3(ray.origin, mult_nb_vec3(ray.direction, \
			cy->spec.cy.t0));
		if (dot_vec3(sub_vec3(point_t0, cy->position), cy->direction) < 0 || \
				dot_vec3(sub_vec3(point_t0, cy->spec.cy.cap_pos[1]), \
					cy->direction) > 0)
			cy->spec.cy.t0 = -1;
	}
	if (cy->spec.cy.t1 >= 0)
	{
		point_t1 = add_vec3(ray.origin, \
			mult_nb_vec3(ray.direction, cy->spec.cy.t1));
		if (dot_vec3(sub_vec3(point_t1, cy->position), cy->direction) < 0 || \
				dot_vec3(sub_vec3(point_t1, cy->spec.cy.cap_pos[1]), \
					cy->direction) > 0)
			cy->spec.cy.t1 = -1;
	}
}
/*Filtrage des intersections en dehors des limites de hauteur*/

static double	find_closest_intersection(t_ray ray, t_object *cy, t_hit *hit)
{
	double	t_min;

	t_min = -1;
	if (cy->spec.cy.t0 > 0 && (t_min < 0 || cy->spec.cy.t0 < t_min))
	{
		t_min = cy->spec.cy.t0;
		hit->normal = get_normal_cy_at_pos(ray, cy, t_min, 0);
	}
	if (cy->spec.cy.t1 > 0 && (t_min < 0 || cy->spec.cy.t1 < t_min) \
		&& (cy->spec.cy.t_cap[0] == -1 || cy->spec.cy.t_cap[1] == -1))
	{
		t_min = cy->spec.cy.t1;
		hit->normal = get_normal_cy_at_pos(ray, cy, t_min, 1);
	}
	if (cy->spec.cy.t_cap[0] > 0 && (t_min < 0 || cy->spec.cy.t_cap[0] < t_min))
	{
		t_min = cy->spec.cy.t_cap[0];
		hit->normal = get_normal_cy_at_pos(ray, cy, t_min, 2);
	}
	if (cy->spec.cy.t_cap[1] > 0 && (t_min < 0 || cy->spec.cy.t_cap[1] < t_min))
	{
		t_min = cy->spec.cy.t_cap[1];
		hit->normal = get_normal_cy_at_pos(ray, cy, t_min, 3);
	}
	return (t_min);
}

/*Trouver le plus petit (t > 0) et mettre à jour la normale 
(si c'est celle du corps ou celle des caps)*/

double	cylinder_intersection(t_ray ray, t_object *cy, t_hit *hit)
{
	double	t_min;

	calculate_cap_positions(cy);
	calculate_body_intersections(ray, cy, cy->spec.cy.radius);
	filter_body_intersections(ray, cy);
	calculate_cap_intersections(ray, cy, cy->spec.cy.radius);
	t_min = find_closest_intersection(ray, cy, hit);
	return (t_min);
}
/*Calcul de l'intersection avec le cylindre*/