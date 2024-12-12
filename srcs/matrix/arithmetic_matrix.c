/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:13:12 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/12 16:13:13 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_mat	multiply_matrix(t_mat a, t_mat b)
{
	t_mat	mat;
	int		i;
	int		j;
	int		k;

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
	return (mat);
}

t_mat	mult_float_matrix(float a, t_mat b)
{
	t_mat	res;

	res.mat[0][0] = b.mat[0][0] * a;
	res.mat[0][1] = b.mat[0][1] * a;
	res.mat[0][2] = b.mat[0][2] * a;
	res.mat[1][0] = b.mat[1][0] * a;
	res.mat[1][1] = b.mat[1][1] * a;
	res.mat[1][2] = b.mat[1][2] * a;
	res.mat[2][0] = b.mat[2][0] * a;
	res.mat[2][1] = b.mat[2][1] * a;
	res.mat[2][2] = b.mat[2][2] * a;
	return (res);
}

t_mat	add_mat(t_mat m1, t_mat m2)
{
	t_mat	res;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res.mat[i][j] = m1.mat[i][j] + m2.mat[i][j];
			j++;
		}
		i++;
	}
	return (res);
}
