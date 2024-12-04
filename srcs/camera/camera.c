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

float	theta_calc(t_vec3 world_dir, t_vec3 cam_dir)
{
	float	theta;
	t_vec3	cross;

	cross = cross_vec3(world_dir, cam_dir);
	theta = atan2(norm_vec3(cross), dot_vec3(world_dir, cam_dir));
	return (theta);
}

t_mat	rodrigues_rot(t_minirt *mini, t_vec3 axis, float theta)
{
	t_vec3	w;
	t_mat	k;
	t_mat	m1;
	t_mat	m2;

	w = cross_vec3(axis, mini->cam.direction);
	w = normalize_vec3(w);
	if (theta * mini->to_degree == 0)
		return (matrix_identity());
	if ((int)(theta * mini->to_degree) == 180)
		return (mult_float_matrix(-1, matrix_identity()));
	k = mat_k(w);
	m1 = mult_float_matrix(sin(theta), k);
	m2 = mult_float_matrix(1 - cos(theta), multiply_matrix(k, k));
	return (add_mat(add_mat(matrix_identity(), m1), m2));
}
