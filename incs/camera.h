#ifndef CAMERA_H
#define CAMERA_H

# include "miniRT.h"

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	float	FOV; //penser a convertir les angles recus en radian = angle * PI/180
	float	to_radian; // a initialiser : M_PI / 180 // a voir pour mettre dans la structure principale car sera utilise plein de fois a plein d'endroit pour les calculs
	float	to_degree; // radian / 180 * PI -> 180 / M_PI

}	t_camera;

#endif