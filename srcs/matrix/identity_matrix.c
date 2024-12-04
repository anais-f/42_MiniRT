#include "miniRT.h"
#include "camera.h"

t_mat	matrix_identity(void)
{
	t_mat	mat;

	mat.mat[0][0] = 1;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = 1;
	mat.mat[1][2] = 0;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = 1;
	return (mat);
}
