#include "camera.h"
#include "miniRT.h"
#include "vector.h"


void	camera(t_minirt *mini)
{
	t_vec3 u =(t_vec3){0, 0, 1};
	t_vec3 v = normalize_vec3(mini->cam.direction);
	t_vec3 w = cross_vec3(u, v);
	float w_norm = norm_vec3(w);
	w = normalize_vec3(w);
	t_mat I = matrix_identity();
	float theta;
	t_mat k;
	t_mat k2;

	k.mat[0][0] = 0;
	k.mat[0][1] = -w.z;
	k.mat[0][2] = w.y;
	k.mat[1][0] = w.z;
	k.mat[1][1] = 0;
	k.mat[1][2] = -w.x;
	k.mat[2][0] = -w.y;
	k.mat[2][1] = w.x;
	k.mat[2][2] = 0;

	printf("dot product = %f\n", dot_vec3(u, v));
	theta = atan2(w_norm, dot_vec3(u, v));
	k2 = multiply_matrix(k, k);
	t_mat m1 = mult_float_matrix(sin(theta), k);
	t_mat m2 = mult_float_matrix(1 - cos(theta), k2);

	mini->cam.rotation_matrix = add_mat(add_mat(I, m1), m2);

	printf("theta = %f\n", theta);	
	printf("theta degree = %f\n", theta * 180 / M_PI);
	
	// https://www.geogebra.org/3d/d8tfhpvh
}





//CREER 2 matrices de rotation pour x et y


//arc cosinus -> avec la valeur entre -1 et 1, retourne l'angle en radian
//cosinus -> pour un angle retourne un rapport entre le cote adjacent et l'hypotenuse
//sinus -> pour un angle retourne un rapport entre le cote oppose et l'hypotenuse
//tan -> pour un angle retourne un rapport entre le cote oppose et le cote adjacent	



