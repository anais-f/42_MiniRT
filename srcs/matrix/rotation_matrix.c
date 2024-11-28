#include "miniRT.h"
#include "camera.h"

t_mat	rotation_matrix_x(double theta)
{
	t_mat mat;

	mat.mat[0][0] = 1;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = cos(theta);
	mat.mat[1][2] = -sin(theta);
	mat.mat[2][0] = 0;
	mat.mat[2][1] = sin(theta);
	mat.mat[2][2] = cos(theta);
	return(mat);
}

t_mat	rotation_matrix_y(double theta)
{
	t_mat mat;

	mat.mat[0][0] = cos(theta);
	mat.mat[0][1] = 0;
	mat.mat[0][2] = sin(theta);
	mat.mat[1][0] = 0;
	mat.mat[1][1] = 1;
	mat.mat[1][2] = 0;
	mat.mat[2][0] = -sin(theta);
	mat.mat[2][1] = 0;
	mat.mat[2][2] = cos(theta);
	return(mat);
}