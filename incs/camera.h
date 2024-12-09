#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "stdbool.h"

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	world_dir;
	float	FOV;
	float	fov_scale;
	float	aspect_ratio; 
	bool	is_init;
	t_mat	rot_mat;
	float	theta;
	t_vec3	normal_rot;
}	t_camera;



#endif