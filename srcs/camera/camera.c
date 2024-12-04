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

	theta = atan2(norm_vec3(w), dot_vec3(u, v));
	return (theta);
}

t_mat	rodrigues_rot(t_minirt *mini, t_vec3 cam_dir, t_vec3 world_dir)
{
	float	theta;
	t_vec3	w;
	t_mat	m1;
	t_mat	m2;

	w = cross_vec3(world_dir, cam_dir);
	theta = theta_calc(world_dir, cam_dir, w);
	w = normalize_vec3(w);
	if (theta * mini->to_degree == 0)
	{
	//	mini->cam.rotation_matrix = matrix_identity();
		return (matrix_identity());
	}
	if ((int)(theta * mini->to_degree) == 180)
	{
		//mini->cam.rotation_matrix = mult_float_matrix(-1, matrix_identity());
		return (mult_float_matrix(-1, matrix_identity()));
	}
	m1 = mult_float_matrix(sin(theta), mat_k(w));
	m2 = mult_float_matrix(1 - cos(theta), multiply_matrix(mat_k(w), mat_k(w)));
	//mini->cam.rotation_matrix = add_mat(add_mat(matrix_identity(), m1), m2);
	printf("cam direction x: %f y: %f z: %f\n", cam_dir.x, cam_dir.y, cam_dir.z);
	return (add_mat(add_mat(matrix_identity(), m1), m2));
}
