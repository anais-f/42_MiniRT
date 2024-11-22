#ifndef OBJECTS_H
# define OBJECTS_H

#include "color.h"
#include "vector.h"
#include <stdbool.h>

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
	double	radius; // a diviser au parsing car on recoit le diametre
}	t_sphere;


typedef struct s_cylinder
{

	double	radius; // a diviser par deux au parsing car on recoit le diametre
	double	height;
}	t_cylinder;

typedef union u_spec
{
	t_sphere	sphere;
	t_cylinder	cylinder;
}	t_spec;

typedef struct s_object
{
	t_object_type	type;
	t_spec			spec;
	t_vec3			position;
	t_vec3			direction;
	t_color			color;
}	t_object;

#endif