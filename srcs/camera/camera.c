#include "camera.h"
#include "miniRT.h"
#include "vector.h"

static t_mat	mat_k(t_vec3 w)
{
	t_mat	k;

	k.mat[0][0] = 0;
	k.mat[0][1] = -w.z;
	k.mat[0][2] = w.y;
	k.mat[1][0] = w.z;
	k.mat[1][1] = 0;
	k.mat[1][2] = -w.x;
	k.mat[2][0] = -w.y;
	k.mat[2][1] = w.x;
	k.mat[2][2] = 0;
	return (k);
}

static float	theta_calc(t_vec3 u, t_vec3 v, t_vec3 w)
{
	float	theta;

	w = cross_vec3(u, v);
	theta = atan2(norm_vec3(w), dot_vec3(u, v));
	return (theta);
}

void	camera(t_minirt *mini, t_vec3 cam_dir, t_vec3 world_dir)
{
	float	theta;
	t_vec3	w;
	t_mat	m1;
	t_mat	m2;

	cam_dir = normalize_vec3(cam_dir);
	w = cross_vec3(world_dir, cam_dir);
	theta = theta_calc(world_dir, cam_dir, w);
	w = normalize_vec3(w);
	if (theta * mini->to_degree == 0)
	{
		mini->cam.rotation_matrix = matrix_identity();
		return ;
	}
	if ((int)(theta * mini->to_degree) == 180)
	{
		mini->cam.rotation_matrix = mult_float_matrix(-1, matrix_identity());
		return ;
	}
	m1 = mult_float_matrix(sin(theta), mat_k(w));
	m2 = mult_float_matrix(1 - cos(theta), multiply_matrix(mat_k(w), mat_k(w)));
	mini->cam.rotation_matrix = add_mat(add_mat(matrix_identity(), m1), m2);
}
