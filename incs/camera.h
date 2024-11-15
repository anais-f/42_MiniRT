#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "stdbool.h" // A redefinir si on inclut rt.h ou juste bool dans les header de struct

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	float	FOV; //penser a convertir les angles recus en radian = angle * PI/180
	float	ratio; // ratio = width / height
	bool	is_init;
}	t_camera;


#endif