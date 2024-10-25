#ifndef CAMERA_H
#define CAMERA_H

# include "miniRT.h"

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	unsigned char	FOV;

}	t_camera;

#endif