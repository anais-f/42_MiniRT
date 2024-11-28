#include "camera.h"
#include "miniRT.h"

float	calcul_theta_y(t_minirt *minirt, t_mat rotation_x)
{
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	float	theta_y;
	float	sign = 0;

	t_vec3 tmp = mult_vec3_matrix((t_vec3){0,0,1}, rotation_x);

	v1.x = tmp.x;
	v1.y = tmp.z;
	v2.x = minirt->cam.direction.x;
	v2.y = minirt->cam.direction.z;
	if (!v1.x && !v1.y)
		return (0);
	if (!v2.x && !v2.y)
		return (0);
	v1 = normalize_vec2(v1);
	v2 = normalize_vec2(v2);
	theta_y = acos(dot_vec2(v1, v2));
	sign = (v1.x * v2.y) - (v1.y * v2.x);
	if (sign > 0)
		theta_y = -theta_y;
	return (theta_y);
}

float	calcul_theta_x(t_minirt *minirt)
{
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	float	theta_x;
	float	sign = 0;

	v1.x = 0;
	v1.y = 1;
	v2.x = minirt->cam.direction.y;
	v2.y = minirt->cam.direction.z;
	if (!v2.x && !v2.y)
		return (0);
	v2 = normalize_vec2(v2);
	theta_x = acos(dot_vec2(v1, v2));
	sign = (v1.x * v2.y) - (v1.y * v2.x);
	if (sign < 0)
		theta_x = -theta_x;
	return (theta_x);
}
void	camera_y(t_minirt *minirt, t_mat rotation_x)
{
	//float theta_x = calcul_theta_x(minirt);
	float theta_y = calcul_theta_y(minirt, rotation_x);
	//t_mat	rotation_x;
	t_mat	rotation_y;

	//rotation_x = rotation_matrix_x(theta_x);
	rotation_y = rotation_matrix_y(theta_y);
	minirt->cam.rotation_matrix = multiply_matrix(rotation_x, rotation_y);
	printf("matrix x * y\n");	
	print_matrix(minirt->cam.rotation_matrix);
	// minirt->cam.rotation_matrix = multiply_matrix(rotation_y, rotation_x);
	// printf("matrix y * x\n\n");	
	// print_matrix(minirt->cam.rotation_matrix);

	printf("radian theta_y = %f\n", theta_y);
	printf("degree theta_y = %f\n",theta_y * 180 / M_PI);
}

void	camera_x(t_minirt *minirt)
{
	float theta_x = calcul_theta_x(minirt);
	//float theta_y = calcul_theta_y(minirt);
	t_mat	rotation_x;
	//t_mat	rotation_y;

	rotation_x = rotation_matrix_x(theta_x);
//rotation_y = rotation_matrix_y(rotation_x);

	camera_y(minirt, rotation_x);
	// print_matrix(minirt->cam.rotation_matrix);
	// minirt->cam.rotation_matrix = multiply_matrix(rotation_y, rotation_x);
	// printf("matrix y * x\n\n");	
	// print_matrix(minirt->cam.rotation_matrix);

	printf("radian theta_x = %f\n", theta_x);
	printf("degree theta_x = %f\n", theta_x * 180 / M_PI);
}

void	camera(t_minirt *minirt)
{

	camera_x(minirt);

}


//CREER 2 matrices de rotation pour x et y


//arc cosinus -> avec la valeur entre -1 et 1, retourne l'angle en radian
//cosinus -> pour un angle retourne un rapport entre le cote adjacent et l'hypotenuse
//sinus -> pour un angle retourne un rapport entre le cote oppose et l'hypotenuse
//tan -> pour un angle retourne un rapport entre le cote oppose et le cote adjacent	



