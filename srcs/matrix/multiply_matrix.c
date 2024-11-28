#include "miniRT.h"
#include "camera.h"

t_mat	multiply_matrix(t_mat a, t_mat b)
{
	t_mat mat;
	int i; // ligne
	int j; // colonne
	int k; // colonne de a et ligne de b

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mat.mat[i][j] = 0;
			k = 0;
			while (k < 3)
			{
				mat.mat[i][j] += a.mat[i][k] * b.mat[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return(mat);
}
/* Multiplication detaillee 

	mat.mat[0][0] = a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0] + a.mat[0][2] * b.mat[2][0];
	mat.mat[0][1] = a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1] + a.mat[0][2] * b.mat[2][1];
	mat.mat[0][2] = a.mat[0][0] * b.mat[0][2] + a.mat[0][1] * b.mat[1][2] + a.mat[0][2] * b.mat[2][2];

	mat.mat[1][0] = a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0] + a.mat[1][2] * b.mat[2][0];
	mat.mat[1][1] = a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1] + a.mat[1][2] * b.mat[2][1];
	mat.mat[1][2] = a.mat[1][0] * b.mat[0][2] + a.mat[1][1] * b.mat[1][2] + a.mat[1][2] * b.mat[2][2];

	mat.mat[2][0] = a.mat[2][0] * b.mat[0][0] + a.mat[2][1] * b.mat[1][0] + a.mat[2][2] * b.mat[2][0];
	mat.mat[2][1] = a.mat[2][0] * b.mat[0][1] + a.mat[2][1] * b.mat[1][1] + a.mat[2][2] * b.mat[2][1];
	mat.mat[2][2] = a.mat[2][0] * b.mat[0][2] + a.mat[2][1] * b.mat[1][2] + a.mat[2][2] * b.mat[2][2];

*/

