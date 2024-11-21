#ifndef OBJECTS_H
# define OBJECTS_H

#include "color.h"
#include "vector.h"

typedef struct light
{
	t_vec3	position;
	t_color	color;
	float	brightness;
	bool	is_init;
}	t_light;

typedef struct ambient_light
{
	t_color	color;
	float	brightness;
	bool	is_init;
}	t_ambient_light;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef struct sphere
{
	float	radius; // a diviser au parsing car on recoit le diametre
}	t_sphere;


typedef struct cylinder
{

	float	radius; // a diviser par deux au parsing car on recoit le diametre
	float	height;
}	t_cylinder;

typedef union u_spec
{
	t_sphere	sphere;
	t_cylinder	cylinder;
}	t_spec;

typedef struct object
{
	t_object_type	type; // voir si pointeur de fonction apres
	t_spec			spec;
	t_vec3			position;
	t_vec3			direction;
	t_color			color;
}	t_object;



#endif