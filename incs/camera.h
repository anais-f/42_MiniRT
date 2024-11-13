#ifndef CAMERA_H
#define CAMERA_H

# include "miniRT.h"

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	float	FOV; //penser a convertir les angles recus en radian = angle * PI/180
	float	ratio; // ratio = width / height


}	t_camera;

#endif