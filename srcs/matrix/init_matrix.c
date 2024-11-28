#include "miniRT.h"
#include "camera.h"


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

