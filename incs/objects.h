/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:00 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/11 13:43:21 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "color.h"
# include "vector.h"
# include <stdbool.h>
# include <math.h>

typedef struct s_minirt	t_minirt;
typedef struct s_hit	t_hit;
typedef struct s_ray	t_ray;
typedef struct s_camera	t_camera;

typedef struct s_light
{
	t_vec3	position;
	t_color	color;
	double	brightness;
	bool	is_init;
}	t_light;

typedef struct s_ambient_light
{
	t_color	color;
	double	brightness;
	bool	is_init;
}	t_ambient_light;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef struct s_sphere
{
	double	radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3	cap_pos[2];
	double	radius;
	double	height;
	double	t0;
	double	t1;
	double	t_cap[2];
}	t_cylinder;

typedef union u_spec
{
	t_sphere	sphere;
	t_cylinder	cy;
}	t_spec;

typedef struct s_object
{
	t_object_type	type;
	t_spec			spec;
	t_vec3			position;
	t_vec3			direction;
	t_color			color;
}	t_object;

/* Common functions */
void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit);
double	object_intersection(t_ray ray, t_object object, t_hit *hit);
t_vec3	get_normal(t_camera cam, t_hit hit);

/* Sphere */
double	sphere_intersection(t_ray ray, t_object sphere);
t_vec3	get_normal_sphere(t_camera cam, t_hit hit);

/* Plane */
double	plane_intersection(t_ray ray, t_object plan);
t_vec3	get_normal_plane(t_camera cam, t_hit hit);

/* Cylinder */
double	cylinder_intersection(t_ray ray, t_object *cylinder, t_hit *hit);
void	calculate_cap_positions(t_object *cy);
void	calculate_cap_intersections(t_ray ray, \
		t_object *cy, double radius);

#endif