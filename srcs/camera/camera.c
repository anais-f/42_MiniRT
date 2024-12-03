#include "camera.h"
#include "miniRT.h"
#include "vector.h"

	// https://www.geogebra.org/3d/d8tfhpvh

t_mat	antisymmetrical_mat(t_vec3 w)
{
	
	t_mat k;

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

void	camera(t_minirt *mini, t_vec3 v)
{
	const t_vec3 u =(t_vec3){0, 0, 1};

	t_vec3 w = cross_vec3(u, v);
	float w_norm = norm_vec3(w);
	w = normalize_vec3(w);
	t_mat identity = matrix_identity();
	
	float theta;
	t_mat m1;
	t_mat m2;

	t_mat k = antisymmetrical_mat(w);


	theta = atan2(w_norm, dot_vec3(u, v));
	
	if (theta * mini->to_degree == 0)
	{
		mini->cam.rotation_matrix = identity;
		return;
	}
	if ((int)(theta * mini->to_degree) == 180)
	{
		mini->cam.rotation_matrix = mult_float_matrix(-1, identity);
		return;
	}


	m1 = mult_float_matrix(sin(theta), k);
	m2 = mult_float_matrix(1 - cos(theta),multiply_matrix(k, k));
	mini->cam.rotation_matrix = add_mat(add_mat(identity, m1), m2);

	
}

float	theta_calc(t_vec3 u, t_vec3 v)
{
	float theta;
	t_vec3 w;

	w = cross_vec3(u, v);
	theta = atan2(norm_vec3(w), dot_vec3(u, v));
	return (theta);
}

