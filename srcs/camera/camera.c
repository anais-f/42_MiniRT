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



double	calcul_theta_y(t_minirt *minirt)
{
	// pour calcul de axe Y
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	double theta_y;
	float sign = 0;

	v1.x = 0;
	v1.y = 1;
	v2.x = minirt->cam.direction.x;
	v2.y = minirt->cam.direction.z;
	v2 = normalize_vec2(v2);

	theta_y = acos(dot_vec2(v1, v2));
	printf("acos y = %f\n", theta_y);
	sign = sin(theta_y); // on aurait pu faire un produit vectoriel egalement pour avoir le sens
	// le sinus renvoit sur l'axe si la longueur est positive ou negative	
	printf("sign sinus y = %f\n", sign);
	sign = 0;
	sign = (v1.x * v2.y) - (v1.y * v2.x);
	theta_y = (v1.x * v2.y) - (v1.y * v2.x);
	printf("sign cross y = %f\n", sign);
	// if (sign < 0)
	// 	theta_y = -theta_y;

	theta_y = atan2(v2.y - v1.y, v2.x - v1.x);

	// sign = atan2((v1.x * v2.y) - (v1.y * v2.x), dot_vec2(v1, v2));
	printf("sign arctan2 y = %f\n", theta_y);

	return (theta_y);
}

double	calcul_theta_x(t_minirt *minirt)
{
	// pour calcul de axe X
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	double theta_x;
	float sign = 0;

	v1.x = 0;
	v1.y = 1;
	v2.x = minirt->cam.direction.y;
	v2.y = minirt->cam.direction.z;
	v2 = normalize_vec2(v2);
	
	theta_x = acos(dot_vec2(v1, v2));
	printf("acos x = %f\n", theta_x);
	sign = sin(theta_x);
	printf("sign sinus x = %f\n", sign);
	sign = 0;
	sign = (v1.x * v2.y) - (v1.y * v2.x);
	theta_x = (v1.x * v2.y) - (v1.y * v2.x);
	printf("sign cross x = %f\n", sign);
	// if (sign < 0)
	// 	theta_x = -theta_x;

	theta_x = atan2(v2.y - v1.y, v2.x - v1.x);

	// sign = atan2((v1.x * v2.y) - (v1.y * v2.x), dot_vec2(v1, v2));
	printf("sign atan2 x = %f\n", theta_x	);

	return (theta_x);
}

void	camera(t_minirt *minirt)
{
	double theta_x = calcul_theta_x(minirt);
	double theta_y = calcul_theta_y(minirt);
	printf("theta_x = %f, theta_y = %f\n", theta_x, theta_y);
}


//arc cosinus -> avec la valeur entre -1 et 1, retourne l'angle en radian
//cosinus -> pour un angle retourne un rapport entre le cote adjacent et l'hypotenuse
//sinus -> pour un angle retourne un rapport entre le cote oppose et l'hypotenuse
//tan -> pour un angle retourne un rapport entre le cote oppose et le cote adjacent	


// 	float fov_scale = tan(cam.FOV * 0.5); // a mettre dans t_camera
// 	coord.px = (2 * (coord.px + 0.5) / (float)WIDTH_WIN - 1) * cam.ratio * fov_scale;
// 	coord.py = (1 - 2 * (coord.py + 0.5) / (float)HEIGHT_WIN) * fov_scale;
