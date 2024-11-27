#include "camera.h"
#include "miniRT.h"

void	init_matrix(t_matrix *matrix)
{
	matrix->matrix[0][0] = 1;
	matrix->matrix[0][1] = 0;
	matrix->matrix[0][2] = 0;
	matrix->matrix[1][0] = 0;
	matrix->matrix[1][1] = 1;
	matrix->matrix[1][2] = 0;
	matrix->matrix[2][0] = 0;
	matrix->matrix[2][1] = 0;
	matrix->matrix[2][2] = 1;
}
//matrice d'identite



double	calcul_axis_y(t_minirt *minirt)
{
	// pour calcul de axe Y
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	double theta_y;

	v1.x = 0;
	v1.y = 1;
	v2.x = minirt->cam.direction.x;
	v2.y = minirt->cam.direction.z;
	v2 = normalize_vec2(v2);

	theta_y = acos(dot_vec2(v1, v2));
	return (theta_y);
}

double	calcul_axis_x(t_minirt *minirt)
{
	// pour calcul de axe X
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	double theta_x;

	v1.x = 0;
	v1.y = 1;
	v2.x = minirt->cam.direction.y;
	v2.y = minirt->cam.direction.z;
	v2 = normalize_vec2(v2);
	
	theta_x = acos(dot_vec2(v1, v2));
	return (theta_x);
}

void	camera(t_minirt *minirt)
{
	double theta_x = calcul_axis_x(minirt);
	double theta_y = calcul_axis_y(minirt);
	printf("theta_x = %f, theta_y = %f\n", theta_x, theta_y);
}




// 	float fov_scale = tan(cam.FOV * 0.5); // a mettre dans t_camera
// 	coord.px = (2 * (coord.px + 0.5) / (float)WIDTH_WIN - 1) * cam.ratio * fov_scale;
// 	coord.py = (1 - 2 * (coord.py + 0.5) / (float)HEIGHT_WIN) * fov_scale;
